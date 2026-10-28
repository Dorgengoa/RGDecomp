/* SPDX-License-Identifier: CC0-1.0 */
/* Shared helpers for the GS tests: a tiny check framework and GIF packet
 * builders (tests drive the GS through real GIF packets wherever possible). */
#ifndef RG_GS_TEST_UTIL_H
#define RG_GS_TEST_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gs.h"

extern int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 30) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { unsigned long long _a = (unsigned long long)(a), \
    _b = (unsigned long long)(b); if (_a != _b) { g_fail++; if (g_fail < 30) \
    fprintf(stderr, "%s:%d: %s == 0x%llX, expected %s == 0x%llX\n", __FILE__, \
            __LINE__, #a, _a, #b, _b); } } while (0)

/* ---- packet builder ---- */
typedef struct pk {
    uint64_t q[2 * 65536];
    uint32_t n; /* qwords */
} pk;

static inline void pk_reset(pk *p) { p->n = 0; }
static inline void pk_qw(pk *p, uint64_t lo, uint64_t hi)
{
    p->q[2 * p->n] = lo; p->q[2 * p->n + 1] = hi; p->n++;
}
static inline void pk_tag(pk *p, uint32_t nloop, int eop, int pre, uint32_t prim,
                          int flg, uint32_t nreg, uint64_t regs)
{
    pk_qw(p, (uint64_t)nloop | ((uint64_t)eop << 15) | ((uint64_t)pre << 46) |
                 ((uint64_t)prim << 47) | ((uint64_t)flg << 58) |
                 ((uint64_t)(nreg & 15) << 60), regs);
}
static inline void pk_ad(pk *p, uint32_t reg, uint64_t v) { pk_qw(p, v, reg); }
static inline void pk_send(gs_state *gs, int path, pk *p)
{
    gs_gif_write(gs, path, p->q, p->n);
    p->n = 0;
}

/* one A+D register write through a complete PATH3 packet */
static inline void ad(gs_state *gs, uint32_t reg, uint64_t v)
{
    static pk p;
    pk_reset(&p);
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, reg, v);
    pk_send(gs, GS_PATH3, &p);
}

/* register value builders */
static inline uint64_t r_frame(uint32_t fbp, uint32_t fbw, uint32_t psm, uint32_t msk)
{ return fbp | ((uint64_t)fbw << 16) | ((uint64_t)psm << 24) | ((uint64_t)msk << 32); }
static inline uint64_t r_zbuf(uint32_t zbp, uint32_t psm, int zmsk)
{ return zbp | ((uint64_t)(psm & 15) << 24) | ((uint64_t)zmsk << 32); }
static inline uint64_t r_scissor(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1)
{ return x0 | ((uint64_t)x1 << 16) | ((uint64_t)y0 << 32) | ((uint64_t)y1 << 48); }
static inline uint64_t r_test(int ate, int atst, uint32_t aref, int afail, int date,
                              int datm, int zte, int ztst)
{
    return (uint64_t)ate | ((uint64_t)atst << 1) | ((uint64_t)aref << 4) |
           ((uint64_t)afail << 12) | ((uint64_t)date << 14) | ((uint64_t)datm << 15) |
           ((uint64_t)zte << 16) | ((uint64_t)ztst << 17);
}
static inline uint64_t r_alpha(int a, int b, int c, int d, uint32_t fix)
{ return (uint64_t)a | ((uint64_t)b << 2) | ((uint64_t)c << 4) | ((uint64_t)d << 6) | ((uint64_t)fix << 32); }
static inline uint64_t r_tex0(uint32_t tbp, uint32_t tbw, uint32_t psm, uint32_t tw,
                              uint32_t th, int tcc, int tfx, uint32_t cbp,
                              uint32_t cpsm, int csm, uint32_t csa, int cld)
{
    return tbp | ((uint64_t)tbw << 14) | ((uint64_t)psm << 20) | ((uint64_t)tw << 26) |
           ((uint64_t)th << 30) | ((uint64_t)tcc << 34) | ((uint64_t)tfx << 35) |
           ((uint64_t)cbp << 37) | ((uint64_t)cpsm << 51) | ((uint64_t)csm << 55) |
           ((uint64_t)csa << 56) | ((uint64_t)cld << 61);
}
static inline uint64_t r_rgbaq(uint32_t r, uint32_t g, uint32_t b, uint32_t a, float q)
{
    uint32_t qu; memcpy(&qu, &q, 4);
    return r | (g << 8) | (b << 16) | ((uint64_t)a << 24) | ((uint64_t)qu << 32);
}
static inline uint64_t r_xyz(uint32_t x16, uint32_t y16, uint32_t z)
{ return x16 | ((uint64_t)y16 << 16) | ((uint64_t)z << 32); }
static inline uint64_t r_st(float s, float t)
{
    uint32_t a, b; memcpy(&a, &s, 4); memcpy(&b, &t, 4);
    return a | ((uint64_t)b << 32);
}

/* host->local upload of a byte stream into a rectangle */
static inline void upload(gs_state *gs, uint32_t dbp, uint32_t dbw, uint32_t dpsm,
                          uint32_t dx, uint32_t dy, uint32_t w, uint32_t h,
                          const uint8_t *data, uint32_t nbytes)
{
    static pk p;
    pk_reset(&p);
    pk_tag(&p, 4, 0, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_BITBLTBUF, ((uint64_t)dbp << 32) | ((uint64_t)dbw << 48) | ((uint64_t)dpsm << 56));
    pk_ad(&p, GS_TRXPOS, ((uint64_t)dx << 32) | ((uint64_t)dy << 48));
    pk_ad(&p, GS_TRXREG, w | ((uint64_t)h << 32));
    pk_ad(&p, GS_TRXDIR, 0);
    uint32_t nq = (nbytes + 15) / 16;
    pk_tag(&p, nq, 1, 0, 0, 2, 0, 0);
    for (uint32_t i = 0; i < nq; i++) {
        uint8_t b[16] = { 0 };
        for (uint32_t k = 0; k < 16 && i * 16 + k < nbytes; k++) b[k] = data[i * 16 + k];
        uint64_t lo, hi;
        memcpy(&lo, b, 8); memcpy(&hi, b + 8, 8);
        pk_qw(&p, lo, hi);
    }
    pk_send(gs, GS_PATH3, &p);
}

/* local->host readback; returns bytes read */
static inline uint32_t download(gs_state *gs, uint32_t sbp, uint32_t sbw, uint32_t spsm,
                                uint32_t sx, uint32_t sy, uint32_t w, uint32_t h,
                                uint8_t *out, uint32_t cap)
{
    static pk p;
    pk_reset(&p);
    pk_tag(&p, 4, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_BITBLTBUF, sbp | ((uint64_t)sbw << 16) | ((uint64_t)spsm << 24));
    pk_ad(&p, GS_TRXPOS, sx | ((uint64_t)sy << 16));
    pk_ad(&p, GS_TRXREG, w | ((uint64_t)h << 32));
    pk_ad(&p, GS_TRXDIR, 1);
    pk_send(gs, GS_PATH3, &p);
    return gs_read_fifo(gs, out, cap);
}

/* Standard 64x32 CT32 target at FBP 0, Z32 at page 8, everything passes. */
static inline void std_target(gs_state *gs, uint32_t fpsm, uint32_t zpsm)
{
    ad(gs, GS_FRAME_1, r_frame(0, 1, fpsm, 0));
    ad(gs, GS_ZBUF_1, r_zbuf(8, zpsm, 0));
    ad(gs, GS_SCISSOR_1, r_scissor(0, 63, 0, 31));
    ad(gs, GS_XYOFFSET_1, 0);
    ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(gs, GS_PRMODECONT, 1);
    ad(gs, GS_COLCLAMP, 1);
}

/* flat sprite in whole pixels (x1,y1 exclusive) */
static inline void sprite(gs_state *gs, uint32_t prim_extra, int x0, int y0, int x1,
                          int y1, uint32_t rgba, uint32_t z)
{
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | prim_extra);
    ad(gs, GS_RGBAQ, r_rgbaq(rgba & 255, (rgba >> 8) & 255, (rgba >> 16) & 255, rgba >> 24, 1.0f));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x0 << 4, (uint32_t)y0 << 4, z));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x1 << 4, (uint32_t)y1 << 4, z));
}

static inline uint32_t px32(gs_state *gs, int x, int y)
{
    return gs_read_pixel(gs, GS_PSMCT32, 0, 1, (uint32_t)x, (uint32_t)y);
}

/* tests in the other files */
int test_swizzle(const char *name);
int test_xfer(const char *name);
int test_clut(const char *name);
int test_pixel(const char *name);
int test_prim(const char *name);
int test_gif(const char *name);
int test_display(const char *name);
int test_sinks(const char *name);

#endif
