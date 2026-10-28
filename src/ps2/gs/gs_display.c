/* SPDX-License-Identifier: CC0-1.0 */
/* PCRTC read-out: PMODE / SMODE2 / DISPFBn / DISPLAYn / BGCOLOR -> an RGBA8
 * frame.  docs/GS.md "Display" has the model and its open questions. */
#include "gs_internal.h"

typedef struct circ {
    int en;
    uint32_t fbp, fbw, dbx, dby; int psm;
    int ox, oy, w, h;   /* output-space rectangle */
} circ;

static void circ_get(const gs_state *gs, int i, int en, int frame_lines, circ *c)
{
    uint64_t fb = gs->preg[7 + 2 * i], dp = gs->preg[8 + 2 * i];
    c->en = en;
    c->fbp = GS_BITS(fb, 0, 9) * 32u;
    c->fbw = GS_BITS(fb, 9, 6);
    c->psm = (int)GS_BITS(fb, 15, 5);
    c->dbx = GS_BITS(fb, 32, 11);
    c->dby = GS_BITS(fb, 43, 11);
    int dx = (int)GS_BITS(dp, 0, 12), dy = (int)GS_BITS(dp, 12, 11);
    int magh = (int)GS_BITS(dp, 23, 4) + 1, magv = (int)GS_BITS(dp, 27, 2) + 1;
    int dw = (int)GS_BITS(dp, 32, 12) + 1, dh = (int)GS_BITS(dp, 44, 11) + 1;
    int vu = magv * frame_lines;
    c->w = dw / magh;
    c->h = dh / vu;
    c->ox = dx / magh;
    c->oy = dy / vu;
}

static int circ_px(const gs_state *gs, const circ *c, int x, int y, uint32_t *rgba)
{
    if (!c->en || x < c->ox || y < c->oy || x >= c->ox + c->w || y >= c->oy + c->h)
        return 0;
    uint32_t raw = gs_read_pixel(gs, c->psm, c->fbp, c->fbw,
                                 (c->dbx + (uint32_t)(x - c->ox)) & 2047,
                                 (c->dby + (uint32_t)(y - c->oy)) & 2047);
    uint32_t col = gs_color_from_stored(c->psm, raw);
    if (c->psm == GS_PSMCT24) col |= 0x80000000u;
    *rgba = col;
    return 1;
}

int gs_read_display_now(const gs_state *gs, int field, uint32_t *out,
                        uint32_t out_cap_px, uint32_t *w, uint32_t *h);
int gs_read_display(const gs_state *gs, int field, uint32_t *out, uint32_t out_cap_px, uint32_t *w,
                    uint32_t *h)
{
    gs_async_drain((gs_state *)gs);
    gs_mem_materialize((gs_state *)gs, NULL, 1);   /* (lazy transfers) */
    return gs_read_display_now(gs, field, out, out_cap_px, w, h);
}

int gs_read_display_now(const gs_state *gs, int field, uint32_t *out,
                    uint32_t out_cap_px, uint32_t *w, uint32_t *h)
{
    uint64_t pmode = gs->preg[0], smode2 = gs->preg[2];
    int en1 = (int)GS_BITS(pmode, 0, 1), en2 = (int)GS_BITS(pmode, 1, 1);
    int mmod = (int)GS_BITS(pmode, 5, 1), slbg = (int)GS_BITS(pmode, 7, 1);
    uint32_t alp = GS_BITS(pmode, 8, 8);
    int inter = (int)GS_BITS(smode2, 0, 1), ffmd = (int)GS_BITS(smode2, 1, 1);
    /* In interlaced FRAME mode every field reads every line, so DH counts
     * two display lines per buffer line (libgraph sets DH = 2*height-1). */
    int frame_lines = (inter && ffmd) ? 2 : 1;
    circ c[2];
    circ_get(gs, 0, en1, frame_lines, &c[0]);
    circ_get(gs, 1, en2, frame_lines, &c[1]);
    *w = *h = 0;
    if (!en1 && !en2) return -1;

    int x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (int i = 0; i < 2; i++) {
        if (!c[i].en) continue;
        if (c[i].ox < x0) x0 = c[i].ox;
        if (c[i].oy < y0) y0 = c[i].oy;
        if (c[i].ox + c[i].w > x1) x1 = c[i].ox + c[i].w;
        if (c[i].oy + c[i].h > y1) y1 = c[i].oy + c[i].h;
    }
    int W = x1 - x0, H = y1 - y0;
    if (W <= 0 || H <= 0) return -1;
    /* a single field of FIELD-mode interlace = every other line */
    int fsel = (field >= 0 && inter && !ffmd);
    int OH = fsel ? (H - (field & 1) + 1) / 2 : H;
    *w = (uint32_t)W; *h = (uint32_t)OH;
    if ((uint64_t)W * (uint64_t)OH > out_cap_px) return -1;

    uint32_t bg = GS_BITS(gs->preg[14], 0, 24);
    for (int oy = 0; oy < OH; oy++) {
        int y = y0 + (fsel ? oy * 2 + (field & 1) : oy);
        for (int ox = 0; ox < W; ox++) {
            int x = x0 + ox;
            uint32_t p1 = 0, p2 = 0, base;
            int h1 = circ_px(gs, &c[0], x, y, &p1);
            int h2 = circ_px(gs, &c[1], x, y, &p2);
            base = slbg ? bg : (h2 ? (p2 & 0xFFFFFFu) : 0u);
            uint32_t res = base;
            if (h1) {
                uint32_t a = mmod ? alp : ((p1 >> 24) * 2u > 255u ? 255u : (p1 >> 24) * 2u);
                res = 0;
                for (int ch = 0; ch < 24; ch += 8) {
                    uint32_t s = (p1 >> ch) & 255u, d = (base >> ch) & 255u;
                    res |= ((s * a + d * (255u - a) + 127u) / 255u) << ch;
                }
            }
            out[(size_t)oy * (size_t)W + (size_t)ox] = res | 0xFF000000u;
        }
    }
    return 0;
}
