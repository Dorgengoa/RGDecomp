/* SPDX-License-Identifier: CC0-1.0 */
/* YCbCr -> RGBA for movie frames (docs/MOVIE.md "Colour").
 * BT.601 studio swing, 8-bit fixed point:
 *   R = (298 (Y-16)              + 409 (Cr-128) + 128) >> 8
 *   G = (298 (Y-16) - 100 (Cb-128) - 208 (Cr-128) + 128) >> 8
 *   B = (298 (Y-16) + 516 (Cb-128)                + 128) >> 8
 * Each chroma sample covers 2x2 luma samples (no interpolation), like the IPU's CSC. */
#include <string.h>

#include "movie.h"

static inline uint8_t clamp8(int v) { return (uint8_t)(v < 0 ? 0 : v > 255 ? 255 : v); }

static inline uint32_t pix(int y, int cb, int cr, uint32_t a)
{
    int c = 298 * (y - 16) + 128;
    int d = cb - 128, e = cr - 128;
    uint32_t r = clamp8((c + 409 * e) >> 8);
    uint32_t g = clamp8((c - 100 * d - 208 * e) >> 8);
    uint32_t b = clamp8((c + 516 * d) >> 8);
    return r | (g << 8) | (b << 16) | (a << 24);
}

void rg_mv_to_rgba(const rg_mvframe *f, uint32_t *rgba, int stride_px, uint8_t alpha)
{
    if (!f->y) return;
    for (int y = 0; y < f->height; y++) {
        const uint8_t *py = f->y + y * f->ystride;
        const uint8_t *pb = f->cb + (y >> 1) * f->cstride;
        const uint8_t *pr = f->cr + (y >> 1) * f->cstride;
        uint32_t *o = rgba + (size_t)y * stride_px;
        for (int x = 0; x < f->width; x++) o[x] = pix(py[x], pb[x >> 1], pr[x >> 1], alpha);
    }
}

void rg_mv_to_ps2_blocks(const rg_mvframe *f, uint8_t *dst, uint8_t alpha)
{
    if (!f->y) return;
    int nw = f->width / 16, nh = f->height / 16;
    uint32_t *o = (uint32_t *)(void *)dst;
    for (int bx = 0; bx < nw; bx++)
        for (int by = 0; by < nh; by++) {
            for (int y = 0; y < 16; y++) {
                int yy = by * 16 + y;
                const uint8_t *py = f->y + yy * f->ystride + bx * 16;
                const uint8_t *pb = f->cb + (yy >> 1) * f->cstride + bx * 8;
                const uint8_t *pr = f->cr + (yy >> 1) * f->cstride + bx * 8;
                for (int x = 0; x < 16; x++) *o++ = pix(py[x], pb[x >> 1], pr[x >> 1], alpha);
            }
        }
}

uint64_t rg_mv_frame_hash(const rg_mvframe *f)
{
    uint64_t h = 0xcbf29ce484222325ull;
    if (!f->y) return 0;
    for (int p = 0; p < 3; p++) {
        const uint8_t *base = p == 0 ? f->y : p == 1 ? f->cb : f->cr;
        int w = p ? f->width / 2 : f->width, hh = p ? f->height / 2 : f->height;
        int s = p ? f->cstride : f->ystride;
        for (int y = 0; y < hh; y++) {
            const uint8_t *r = base + y * s;
            for (int x = 0; x < w; x++) {
                h ^= r[x];
                h *= 0x100000001b3ull;
            }
        }
    }
    return h;
}
