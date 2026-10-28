/* SPDX-License-Identifier: CC0-1.0 */
/* Transfers: host->local (IMAGE packets), local->host (TRXDIR=1 readback),
 * local->local (incl. overlap direction) for every PSM. */
#include "gs_test_util.h"

static uint32_t lcg(uint32_t *s) { *s = *s * 1664525u + 1013904223u; return *s >> 8; }

/* decode pixel i from a host stream */
static uint32_t stream_px(const uint8_t *d, int bpp, uint32_t i)
{
    switch (bpp) {
    case 32: return d[4 * i] | (d[4 * i + 1] << 8) | (d[4 * i + 2] << 16) | ((uint32_t)d[4 * i + 3] << 24);
    case 24: return d[3 * i] | (d[3 * i + 1] << 8) | (d[3 * i + 2] << 16);
    case 16: return d[2 * i] | (d[2 * i + 1] << 8);
    case 8: return d[i];
    default: return (i & 1) ? (d[i / 2] >> 4) : (d[i / 2] & 15u);
    }
}

static void roundtrip(int psm)
{
    static uint8_t data[64 * 1024], back[64 * 1024];
    gs_state *gs = gs_create();
    int bpp = gs_psm_bpp(psm);
    const uint32_t W = 38, H = 21, DX = 5, DY = 3, BP = 96, BW = 4;
    uint32_t nbytes = W * H * (uint32_t)bpp / 8;
    uint32_t s = 0x1234u + (uint32_t)psm;
    for (uint32_t i = 0; i < nbytes; i++) data[i] = (uint8_t)lcg(&s);
    memset(gs->vram, 0xA5, GS_VRAM_BYTES);

    upload(gs, BP, BW, (uint32_t)psm, DX, DY, W, H, data, nbytes);

    /* (1) each pixel landed at its swizzled address, in raster order */
    uint32_t bad = 0;
    for (uint32_t j = 0; j < H; j++)
        for (uint32_t i = 0; i < W; i++)
            if (gs_read_pixel(gs, psm, BP, BW, DX + i, DY + j) != stream_px(data, bpp, j * W + i))
                bad++;
    CHECK_EQ(bad, 0);

    /* (2) H formats touch only their bits of the 32-bit word */
    if (psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH) {
        uint32_t other = 0;
        for (uint32_t a = 0; a < GS_VRAM_BYTES; a++)
            if ((a & 3) != 3 && gs->vram[a] != 0xA5) other++;
        CHECK_EQ(other, 0);
        if (psm != GS_PSMT8H) {
            /* the other nibble of byte 3 is preserved */
            uint32_t keep = 0;
            for (uint32_t j = 0; j < H; j++)
                for (uint32_t i = 0; i < W; i++) {
                    uint32_t a = gs_pixel_addr(psm, BP, BW, DX + i, DY + j, NULL);
                    uint8_t v = gs->vram[a + 3];
                    if (psm == GS_PSMT4HL ? (v >> 4) != 0xA : (v & 15) != 5) keep++;
                }
            CHECK_EQ(keep, 0);
        }
    }
    if (psm == GS_PSMCT24 || psm == GS_PSMZ24) {
        uint32_t top = 0;
        for (uint32_t j = 0; j < H; j++)
            for (uint32_t i = 0; i < W; i++) {
                uint32_t a = gs_pixel_addr(psm, BP, BW, DX + i, DY + j, NULL);
                if (gs->vram[a + 3] != 0xA5) top++;
            }
        CHECK_EQ(top, 0);
    }

    /* (3) readback returns the same stream, padded to a qword */
    uint32_t n = download(gs, BP, BW, (uint32_t)psm, DX, DY, W, H, back, sizeof back);
    CHECK_EQ(n, (nbytes + 15) & ~15u);
    CHECK(memcmp(back, data, nbytes) == 0);
    gs_destroy(gs);
}

static void split_upload(void)
{
    /* the IMAGE data of one transfer arrives in several GIF packets, and the
     * 24-bit pixels straddle qword boundaries */
    gs_state *gs = gs_create();
    static pk p;
    uint8_t data[16 * 3 * 4];
    for (int i = 0; i < (int)sizeof data; i++) data[i] = (uint8_t)(i * 7 + 1);
    pk_reset(&p);
    pk_tag(&p, 4, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_BITBLTBUF, ((uint64_t)0 << 32) | ((uint64_t)1 << 48) | ((uint64_t)GS_PSMCT24 << 56));
    pk_ad(&p, GS_TRXPOS, 0);
    pk_ad(&p, GS_TRXREG, 16 | ((uint64_t)4 << 32));
    pk_ad(&p, GS_TRXDIR, 0);
    pk_send(gs, GS_PATH3, &p);
    for (int part = 0; part < 12; part++) {
        uint64_t lo, hi;
        memcpy(&lo, data + part * 16, 8); memcpy(&hi, data + part * 16 + 8, 8);
        pk_tag(&p, 1, 1, 0, 0, 2, 0, 0);
        pk_qw(&p, lo, hi);
        pk_send(gs, GS_PATH3, &p);
    }
    uint32_t bad = 0;
    for (uint32_t i = 0; i < 64; i++)
        if (gs_read_pixel(gs, GS_PSMCT24, 0, 1, i & 15, i >> 4) != stream_px(data, 24, i)) bad++;
    CHECK_EQ(bad, 0);
    /* HWREG through A+D works the same as IMAGE */
    ad(gs, GS_BITBLTBUF, ((uint64_t)0 << 32) | ((uint64_t)1 << 48) | ((uint64_t)GS_PSMCT32 << 56));
    ad(gs, GS_TRXPOS, ((uint64_t)10 << 32) | ((uint64_t)20 << 48));
    ad(gs, GS_TRXREG, 2 | ((uint64_t)1 << 32));
    ad(gs, GS_TRXDIR, 0);
    ad(gs, GS_HWREG, 0x22222222ull << 32 | 0x11111111ull);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT32, 0, 1, 10, 20), 0x11111111u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT32, 0, 1, 11, 20), 0x22222222u);
    gs_destroy(gs);
}

static void l2l(void)
{
    gs_state *gs = gs_create();
    /* fill a 16x16 CT32 area with distinct values, copy to another buffer
     * with a different width and to an overlapping position */
    for (uint32_t y = 0; y < 16; y++)
        for (uint32_t x = 0; x < 16; x++)
            gs_write_pixel(gs, GS_PSMCT32, 0, 1, x, y, 0x1000u * y + x);
    ad(gs, GS_BITBLTBUF, 0 | (1ull << 16) | ((uint64_t)GS_PSMCT32 << 24) |
                             ((uint64_t)320 << 32) | ((uint64_t)3 << 48) | ((uint64_t)GS_PSMCT32 << 56));
    ad(gs, GS_TRXPOS, 2 | (3ull << 16) | (100ull << 32) | (7ull << 48));
    ad(gs, GS_TRXREG, 8 | (5ull << 32));
    ad(gs, GS_TRXDIR, 2);
    uint32_t bad = 0;
    for (uint32_t y = 0; y < 5; y++)
        for (uint32_t x = 0; x < 8; x++)
            if (gs_read_pixel(gs, GS_PSMCT32, 320, 3, 100 + x, 7 + y) != 0x1000u * (y + 3) + x + 2) bad++;
    CHECK_EQ(bad, 0);

    /* overlapping move right by 1 within the same buffer: DIR=0 (UL->LR)
     * smears the first column, DIR=2 (UR->LL) moves correctly */
    for (int dir = 0; dir < 4; dir += 2) {
        for (uint32_t x = 0; x < 8; x++) gs_write_pixel(gs, GS_PSMCT32, 0, 1, x, 30, x + 1);
        ad(gs, GS_BITBLTBUF, 0 | (1ull << 16) | ((uint64_t)GS_PSMCT32 << 24) |
                                 (0ull << 32) | (1ull << 48) | ((uint64_t)GS_PSMCT32 << 56));
        ad(gs, GS_TRXPOS, 0 | (30ull << 16) | (1ull << 32) | (30ull << 48) | ((uint64_t)dir << 59));
        ad(gs, GS_TRXREG, 7 | (1ull << 32));
        ad(gs, GS_TRXDIR, 2);
        for (uint32_t x = 1; x < 8; x++) {
            uint32_t v = gs_read_pixel(gs, GS_PSMCT32, 0, 1, x, 30);
            if (dir == 0) CHECK_EQ(v, 1u);
            else CHECK_EQ(v, x);
        }
    }
    /* T4 -> T4 copy */
    for (uint32_t y = 0; y < 8; y++)
        for (uint32_t x = 0; x < 40; x++)
            gs_write_pixel(gs, GS_PSMT4, 1000, 2, x, y, (x * 3 + y) & 15);
    ad(gs, GS_BITBLTBUF, 1000 | (2ull << 16) | ((uint64_t)GS_PSMT4 << 24) |
                             (1200ull << 32) | (2ull << 48) | ((uint64_t)GS_PSMT4 << 56));
    ad(gs, GS_TRXPOS, 0 | (0ull << 16) | (33ull << 32) | (65ull << 48));
    ad(gs, GS_TRXREG, 40 | (8ull << 32));
    ad(gs, GS_TRXDIR, 2);
    bad = 0;
    for (uint32_t y = 0; y < 8; y++)
        for (uint32_t x = 0; x < 40; x++)
            if (gs_read_pixel(gs, GS_PSMT4, 1200, 2, 33 + x, 65 + y) != ((x * 3 + y) & 15)) bad++;
    CHECK_EQ(bad, 0);
    gs_destroy(gs);
}

static void alias(void)
{
    /* the H formats alias the top of CT32 words; T8 and CT32 share pages */
    gs_state *gs = gs_create();
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 3, 2, 0xAB123456u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT8H, 0, 1, 3, 2), 0xABu);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT4HL, 0, 1, 3, 2), 0xBu);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT4HH, 0, 1, 3, 2), 0xAu);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT24, 0, 1, 3, 2), 0x123456u);
    /* T8 pixel (0,0) is byte 0 of CT32 pixel (0,0); T8 (1,0) is byte 0 of
     * CT32 (1,0) (manual column figure) */
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, 0x44332211u);
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 1, 0, 0x88776655u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT8, 0, 2, 0, 0), 0x11u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT8, 0, 2, 1, 0), 0x55u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMT8, 0, 2, 8, 0), 0x33u);
    gs_destroy(gs);
}

/* ---- bulk IMAGE path (gs_xfer_image, docs/GPU.md "Performance" checkpoint 3) ---- */

static const int k_psms[] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16, GS_PSMCT16S,
                              GS_PSMT8, GS_PSMT4, GS_PSMT8H, GS_PSMT4HL, GS_PSMT4HH,
                              GS_PSMZ32, GS_PSMZ24, GS_PSMZ16, GS_PSMZ16S };
#define N_PSMS (sizeof k_psms / sizeof k_psms[0])

/* address in byte units (nibble units for PSMT4) */
static uint32_t unit_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    int nib = 0;
    uint32_t a = gs_pixel_addr(psm, bp, bw, x, y, &nib);
    return psm == GS_PSMT4 ? (a << 1) | (uint32_t)nib : a;
}

/* the identity gs_xfer_image relies on: addr(x, y) from addr(x, 0) at BP 0,
 * addr(0, y) and addr(0, 0) at BP 0, for every x, y < 2048 */
static void separable(void)
{
    static const uint32_t bws[] = { 1, 2, 3, 4, 5, 8, 10, 16, 20, 33, 63 };
    static const uint32_t bps[] = { 0, 1, 31, 32, 0x2A00, 0x3FFF };
    static uint32_t xt[2048];
    uint32_t bad = 0;
    uint64_t n = 0;
    for (size_t pi = 0; pi < N_PSMS; pi++) {
        int psm = k_psms[pi];
        uint32_t S = psm == GS_PSMT4 ? 9 : 8, L = (1u << S) - 1;
        for (size_t wi = 0; wi < sizeof bws / sizeof bws[0]; wi++)
            for (size_t bi = 0; bi < sizeof bps / sizeof bps[0]; bi++) {
                uint32_t bw = bws[wi], bp = bps[bi];
                /* every y for a few (bp, bw), a stride of 7 rows for the rest */
                uint32_t ystep = (wi < 3 && bi < 2) ? 1 : 7;
                uint32_t o = unit_addr(psm, 0, bw, 0, 0);
                for (uint32_t x = 0; x < 2048; x++) xt[x] = unit_addr(psm, 0, bw, x, 0);
                for (uint32_t y = 0; y < 2048; y += ystep) {
                    uint32_t ya = unit_addr(psm, bp, bw, 0, y);
                    uint32_t yb = (ya >> S) - (o >> S), yl = (ya ^ o) & L;
                    for (uint32_t x = 0; x < 2048; x++) {
                        uint32_t a = (((yb + (xt[x] >> S)) & 0x3FFFu) << S) | ((yl ^ xt[x]) & L);
                        if (a != unit_addr(psm, bp, bw, x, y)) {
                            if (bad < 5)
                                fprintf(stderr, "psm %#x bp %u bw %u x %u y %u\n", psm, bp, bw, x, y);
                            bad++;
                        }
                        n++;
                    }
                }
            }
    }
    printf("separable: %llu addresses checked\n", (unsigned long long)n);
    CHECK_EQ(bad, 0);
}

typedef struct hook_log { uint32_t n; uint32_t ev[64][8]; } hook_log;
static void log_mem(void *user, gs_state *gs, int op, const gs_mem_rect *r)
{
    hook_log *l = (hook_log *)user;
    (void)gs;
    if (l->n < 64) {
        uint32_t *e = l->ev[l->n];
        e[0] = (uint32_t)op; e[1] = r->bp; e[2] = r->bw; e[3] = (uint32_t)r->psm;
        e[4] = r->x; e[5] = r->y; e[6] = r->w; e[7] = r->h;
    }
    l->n++;
}

/* Random transfers: the reference state gets every 64-bit word through
 * gs_write_reg(HWREG) (gs_xfer_hwreg, the per-pixel path); the other the same
 * words as IMAGE packets through gs_gif_write in random pieces (whole and
 * split loops, data past the end, transfers abandoned by a new TRXDIR).
 * Local memory, transfer state, counters, HWREG and the hook calls must be
 * identical. */
static void bulk(int cases, int corrupt)
{
    gs_state *a = gs_create(), *b = gs_create();
    static hook_log la, lb;
    static uint64_t words[2 * 70000];
    static pk p;
    a->hooks.mem = log_mem; a->hooks.user = &la;
    b->hooks.mem = log_mem; b->hooks.user = &lb;
    uint32_t s = 0xC0FFEEu;
    for (uint32_t i = 0; i < GS_VRAM_BYTES; i++) a->vram[i] = (uint8_t)lcg(&s);
    memcpy(b->vram, a->vram, GS_VRAM_BYTES);
    uint32_t bad_mem = 0, bad_state = 0, bad_hook = 0;
    for (int c = 0; c < cases; c++) {
        int psm = k_psms[lcg(&s) % N_PSMS];
        uint32_t r = lcg(&s) % 16;
        uint32_t w, h;
        if (r < 4) { w = 1 + lcg(&s) % 8; h = 1 + lcg(&s) % 8; }
        else if (r < 12) { w = 8u << (lcg(&s) % 6); h = 8u << (lcg(&s) % 5); }
        else if (r < 15) { w = 1 + lcg(&s) % 300; h = 1 + lcg(&s) % 40; }
        else { w = 1 + lcg(&s) % 4095; h = 1 + lcg(&s) % 3; }
        uint32_t dx = (lcg(&s) % 4) ? (lcg(&s) % 8) * 8 : lcg(&s) % 2048;
        uint32_t dy = (lcg(&s) % 4) ? (lcg(&s) % 8) * 8 : lcg(&s) % 2048;
        uint32_t bp = lcg(&s) % 0x4000, bw = 1 + lcg(&s) % 40;
        int bpp = gs_psm_bpp(psm);
        uint32_t bytes = (uint32_t)(((uint64_t)w * h * (uint32_t)bpp + 7) / 8);
        uint32_t nw = (bytes + 7) / 8;
        uint32_t v = lcg(&s) % 8;
        if (v == 0) nw += 1 + lcg(&s) % 5;                  /* data past the end */
        else if (v == 1 && nw > 1) nw = 1 + lcg(&s) % nw;   /* abandoned */
        if (nw & 1) nw++;                                   /* whole qwords */
        if (nw > sizeof words / sizeof words[0]) nw = sizeof words / sizeof words[0];
        for (uint32_t i = 0; i < nw; i++)
            words[i] = ((uint64_t)lcg(&s) << 40) ^ ((uint64_t)lcg(&s) << 20) ^ lcg(&s);
        uint64_t bb = ((uint64_t)bp << 32) | ((uint64_t)bw << 48) | ((uint64_t)psm << 56) |
                      (lcg(&s) & 0x3FFF);
        uint64_t tp = ((uint64_t)dx << 32) | ((uint64_t)dy << 48) | (lcg(&s) & 0x7FF);
        uint64_t tr = w | ((uint64_t)h << 32);
        gs_state *both[2] = { a, b };
        la.n = lb.n = 0;
        for (int k = 0; k < 2; k++) {
            gs_write_reg(both[k], GS_BITBLTBUF, bb);
            gs_write_reg(both[k], GS_TRXPOS, tp);
            gs_write_reg(both[k], GS_TRXREG, tr);
            gs_write_reg(both[k], GS_TRXDIR, 0);
        }
        for (uint32_t i = 0; i < nw; i++) gs_write_reg(a, GS_HWREG, words[i]);
        /* the same words as IMAGE packets: random NLOOPs, each packet sent in
         * random pieces */
        uint32_t nq = nw / 2, q = 0;
        while (q < nq) {
            uint32_t nl = 1 + lcg(&s) % ((lcg(&s) % 2) ? 16 : 4096);
            if (nl > nq - q) nl = nq - q;
            pk_reset(&p);
            pk_tag(&p, nl, 1, 0, 0, 2 + (int)(lcg(&s) & 1), 0, 0);
            for (uint32_t i = 0; i < nl; i++) pk_qw(&p, words[2 * (q + i)], words[2 * (q + i) + 1]);
            if (corrupt && c == 7 && q == 0) p.q[2] ^= 1; /* first pixel's low bit */
            uint32_t sent = 0;
            while (sent < p.n) {
                uint32_t piece = (lcg(&s) % 3) ? p.n - sent : 1 + lcg(&s) % (p.n - sent);
                gs_gif_write(b, GS_PATH3, &p.q[2 * sent], piece);
                sent += piece;
            }
            q += nl;
        }
        /* an unfinished transfer ends with the next TRXDIR */
        if (lcg(&s) % 2) { gs_write_reg(a, GS_TRXDIR, 3); gs_write_reg(b, GS_TRXDIR, 3); }
        if (memcmp(a->vram, b->vram, GS_VRAM_BYTES)) {
            if (bad_mem < 5)
                fprintf(stderr, "case %d psm %#x %ux%u at %u,%u bp %u bw %u: vram differs\n",
                        c, psm, w, h, dx, dy, bp, bw);
            bad_mem++;
            memcpy(b->vram, a->vram, GS_VRAM_BYTES);
        }
        if (a->xfer_x != b->xfer_x || a->xfer_y != b->xfer_y || a->xfer_dir != b->xfer_dir ||
            a->xfer_carry_n != b->xfer_carry_n || memcmp(a->xfer_carry, b->xfer_carry, 8) ||
            a->stats.xfer_h2l_px != b->stats.xfer_h2l_px || a->reg[GS_HWREG] != b->reg[GS_HWREG] ||
            a->hooks.xfer_open != b->hooks.xfer_open) {
            if (bad_state < 5)
                fprintf(stderr, "case %d psm %#x %ux%u: state differs (x,y %u,%u / %u,%u; carry %u / %u;"
                        " px %llu / %llu; hwreg %llx / %llx; open %d / %d)\n",
                        c, psm, w, h, a->xfer_x, a->xfer_y, b->xfer_x, b->xfer_y, a->xfer_carry_n,
                        b->xfer_carry_n, (unsigned long long)a->stats.xfer_h2l_px,
                        (unsigned long long)b->stats.xfer_h2l_px, (unsigned long long)a->reg[GS_HWREG],
                        (unsigned long long)b->reg[GS_HWREG], a->hooks.xfer_open, b->hooks.xfer_open);
            bad_state++;
        }
        if (la.n != lb.n || memcmp(la.ev, lb.ev, sizeof la.ev)) bad_hook++;
    }
    printf("bulk: %d transfers, %llu pixels\n", cases, (unsigned long long)a->stats.xfer_h2l_px);
    CHECK_EQ(bad_mem, 0);
    CHECK_EQ(bad_state, 0);
    CHECK_EQ(bad_hook, 0);
    gs_destroy(a);
    gs_destroy(b);
}


/* gs_xfer_mask: the bits of the first npx pixels of random transfers, against
 * gs_write_pixel of all-ones pixels into zeroed memory (the bits it changes) */
static void xmask(void)
{
    gs_state *g = gs_create();
    uint8_t *m = (uint8_t *)calloc(1, GS_VRAM_BYTES);
    uint32_t s = 0xBEEFu, bad = 0;
    for (int c = 0; c < 400; c++) {
        int psm = k_psms[lcg(&s) % N_PSMS];
        uint32_t w = (lcg(&s) % 3) ? 8u << (lcg(&s) % 5) : 1 + lcg(&s) % 300;
        uint32_t h = (lcg(&s) % 3) ? 8u << (lcg(&s) % 4) : 1 + lcg(&s) % 70;
        uint32_t x = (lcg(&s) % 2) ? (lcg(&s) % 8) * 64 : lcg(&s) % 2048;
        uint32_t y = (lcg(&s) % 2) ? (lcg(&s) % 8) * 32 : lcg(&s) % 2048;
        uint32_t bp = lcg(&s) % 0x4000, bw = 1 + lcg(&s) % 20;
        uint32_t npx = (lcg(&s) % 3) ? w * h : lcg(&s) % (w * h + 1);
        memset(g->vram, 0, GS_VRAM_BYTES);
        memset(m, 0, GS_VRAM_BYTES);
        for (uint32_t k = 0; k < npx; k++)
            gs_write_pixel(g, psm, bp, bw, (x + k % w) & 2047, (y + k / w) & 2047, 0xFFFFFFFFu);
        gs_xfer_mask(psm, bp, bw, x, y, w, h, npx, m);
        if (memcmp(m, g->vram, GS_VRAM_BYTES)) {
            if (bad < 5) fprintf(stderr, "case %d psm %#x %ux%u at %u,%u npx %u: mask differs\n",
                                 c, psm, w, h, x, y, npx);
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    free(m);
    gs_destroy(g);
}

int test_xfer(const char *name)
{
    static const int psms[] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16, GS_PSMCT16S,
                                GS_PSMT8, GS_PSMT4, GS_PSMT8H, GS_PSMT4HL, GS_PSMT4HH,
                                GS_PSMZ32, GS_PSMZ24, GS_PSMZ16, GS_PSMZ16S };
    if (!strcmp(name, "xfer_roundtrip")) {
        for (size_t i = 0; i < sizeof psms / sizeof psms[0]; i++) roundtrip(psms[i]);
        return 1;
    }
    if (!strcmp(name, "xfer_split")) { split_upload(); return 1; }
    if (!strcmp(name, "xfer_l2l")) { l2l(); return 1; }
    if (!strcmp(name, "xfer_alias")) { alias(); return 1; }
    if (!strcmp(name, "xfer_separable")) { separable(); return 1; }
    if (!strcmp(name, "xfer_mask")) { xmask(); return 1; }
    if (!strcmp(name, "xfer_bulk")) { bulk(3000, 0); return 1; }
    if (!strcmp(name, "xfer_bulk_control")) { bulk(50, 1); return 1; }
    return 0;
}
