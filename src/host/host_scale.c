/* SPDX-License-Identifier: CC0-1.0 */
/* Presentation rectangle math (aspect + scaling modes).  Pure. */
#include <string.h>

#include <SDL3/SDL.h>

#include "host_internal.h"

static const char *const k_scale_names[] = { "linear", "nearest", "integer", "stretch" };

const char *rg_scale_name(rg_scale_mode m)
{
    return ((unsigned)m < 4) ? k_scale_names[m] : "?";
}

int rg_scale_from_name(const char *name)
{
    for (int i = 0; i < 4; i++)
        if (!SDL_strcasecmp(name, k_scale_names[i])) return i;
    return -1;
}

/* round(a * b / c) for non-negative ints */
static int muldiv_round(int a, int b, int c)
{
    return (int)(((int64_t)a * b + c / 2) / c);
}

rg_rect rg_fit_rect(int win_w, int win_h, int src_w, int src_h,
                    int aspect_num, int aspect_den, rg_scale_mode mode, int *factor)
{
    rg_rect r = { 0, 0, 0, 0 };
    if (factor) *factor = 0;
    if (win_w <= 0 || win_h <= 0 || src_w <= 0 || src_h <= 0) return r;
    if (mode == RG_SCALE_STRETCH) {
        r.w = win_w; r.h = win_h;
        return r;
    }
    /* displayed shape num:den (square source pixels when unspecified) */
    int an = aspect_num, ad = aspect_den;
    if (an <= 0 || ad <= 0) { an = src_w; ad = src_h; }
    if (mode == RG_SCALE_INTEGER) {
        int n = win_h / src_h;
        while (n >= 1) {
            int h = n * src_h, w = muldiv_round(h, an, ad);
            if (w <= win_w) {
                r.w = w; r.h = h;
                r.x = (win_w - w) / 2; r.y = (win_h - h) / 2;
                if (factor) *factor = n;
                return r;
            }
            n--;
        }
        /* not even 1x fits: fall through to the plain fit */
    }
    /* largest an:ad rectangle inside the window */
    if ((int64_t)win_w * ad <= (int64_t)win_h * an) {
        r.w = win_w;
        r.h = muldiv_round(win_w, ad, an);
    } else {
        r.h = win_h;
        r.w = muldiv_round(win_h, an, ad);
    }
    if (r.w > win_w) r.w = win_w;
    if (r.h > win_h) r.h = win_h;
    if (r.w < 1) r.w = 1;
    if (r.h < 1) r.h = 1;
    r.x = (win_w - r.w) / 2;
    r.y = (win_h - r.h) / 2;
    return r;
}

rg_rect rg_fit_rect_content(int win_w, int win_h, int src_w, int src_h,
                            int aspect_num, int aspect_den, int content_num, int content_den,
                            rg_scale_mode mode, int *factor)
{
    rg_rect r = rg_fit_rect(win_w, win_h, src_w, src_h, aspect_num, aspect_den, mode, factor);
    int an = aspect_num, ad = aspect_den, cn = content_num, cd = content_den;
    if (an <= 0 || ad <= 0) { an = src_w; ad = src_h; }
    if (cn <= 0 || cd <= 0 || r.w <= 0 || r.h <= 0 || (int64_t)cn * ad == (int64_t)an * cd)
        return r;
    rg_rect c = r;
    int64_t num = (int64_t)cn * ad, den = (int64_t)cd * an;   /* content / canvas width ratio */
    if (num < den) {   /* narrower: pillarbox at the canvas height */
        c.w = (int)(((int64_t)r.w * num + den / 2) / den);
        if (c.w < 1) c.w = 1;
    } else {           /* wider: letterbox at the canvas width */
        c.h = (int)(((int64_t)r.h * den + num / 2) / num);
        if (c.h < 1) c.h = 1;
    }
    c.x = r.x + (r.w - c.w) / 2;
    c.y = r.y + (r.h - c.h) / 2;
    return c;
}

int rg_present_image(const uint32_t *src, uint32_t src_w, uint32_t src_h, int aspect_num,
                     int aspect_den, int content_num, int content_den, uint32_t *out,
                     size_t out_cap, uint32_t *out_w)
{
    int an = aspect_num, ad = aspect_den;
    if (an <= 0 || ad <= 0) { an = (int)src_w; ad = (int)src_h; }
    uint32_t cw = (src_w && src_h) ? (uint32_t)muldiv_round((int)src_h, an, ad) : 0;
    if (out_w) *out_w = cw;
    if (!src || !out || !cw || (uint64_t)cw * src_h > out_cap) return -1;
    rg_rect r = rg_fit_rect_content((int)cw, (int)src_h, (int)src_w, (int)src_h, an, ad,
                                    content_num, content_den, RG_SCALE_LINEAR, NULL);
    for (uint32_t i = 0; i < cw * src_h; i++) out[i] = 0xFF000000u;
    if (r.w <= 0 || r.h <= 0) return 0;
    for (int y = 0; y < r.h; y++) {
        /* rows: nearest (r.h == src_h unless the content is wider) */
        uint32_t sy = (uint32_t)(((int64_t)y * src_h + src_h / 2) / r.h);
        if (sy >= src_h) sy = src_h - 1;
        const uint8_t *row = (const uint8_t *)(src + (size_t)sy * src_w);
        uint32_t *o = out + (size_t)(r.y + y) * cw + r.x;
        for (int x = 0; x < r.w; x++) {
            /* centre of output pixel x in source pixels, 8-bit fraction */
            int64_t u = (((int64_t)2 * x + 1) * src_w * 256) / (2 * (int64_t)r.w) - 128;
            if (u < 0) u = 0;
            int64_t umax = ((int64_t)src_w - 1) * 256;
            if (u > umax) u = umax;
            uint32_t i0 = (uint32_t)(u >> 8), f = (uint32_t)(u & 255);
            uint32_t i1 = i0 + 1 < src_w ? i0 + 1 : i0;
            const uint8_t *p0 = row + i0 * 4, *p1 = row + i1 * 4;
            uint32_t px = 0;
            for (int ch = 0; ch < 3; ch++)
                px |= ((p0[ch] * (256 - f) + p1[ch] * f + 128) >> 8) << (8 * ch);
            o[x] = px | 0xFF000000u;
        }
    }
    return 0;
}
