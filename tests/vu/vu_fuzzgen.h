/* SPDX-License-Identifier: CC0-1.0 */
/* Random VU1 programs and states for rg-vu-blkfuzz and rg-vu-progfuzz
 * (docs/VU.md "Block translator").  Only fields that the pre-optimisation
 * reference copy (tests/vu/ref) also has are touched, so the generator
 * builds against either vu.h. */
#ifndef RG_VU_FUZZGEN_H
#define RG_VU_FUZZGEN_H

#include <stdint.h>
#include <string.h>

#include "vu.h"

static uint32_t g_rng = 1;
static uint32_t rnd(void)
{
    g_rng ^= g_rng << 13;
    g_rng ^= g_rng >> 17;
    g_rng ^= g_rng << 5;
    return g_rng;
}
static uint32_t rn(uint32_t n) { return rnd() % n; }

/* PATH1 packets, hashed per state */
typedef struct sinkh { uint64_t h, n; } sinkh;
static void sink(void *u, const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    sinkh *s = (sinkh *)u;
    uint32_t k;
    s->h = (s->h ^ addr) * 0x100000001B3ull;
    for (k = 0; k < bytes; k++) s->h = (s->h ^ d[k]) * 0x100000001B3ull;
    s->n++;
}

static uint32_t rfloat(void)
{
    static const uint32_t special[] = {
        0x00000000u, 0x80000000u, 0x3F800000u, 0xBF800000u, 0x00000001u, 0x807FFFFFu,
        0x7F800000u, 0x7FC00000u, 0xFF800000u, 0x7FFFFFFFu, 0xFFFFFFFFu, 0x00800000u,
        0x40000000u, 0x3F000000u, 0x4B400000u, 0x00400000u};
    switch (rn(4)) {
    case 0: return special[rn(sizeof special / sizeof special[0])];
    case 1: return rnd();
    default: { /* ordinary values near 1, mixed signs */
        uint32_t e = 100 + rn(54);
        return (rnd() & 0x80000000u) | (e << 23) | (rnd() & 0x7FFFFFu);
    }
    }
}

static uint32_t rreg(void) { return rn(8) == 0 ? rn(32) : rn(8); }   /* VF: mostly 0..7 */
static uint32_t rvi(void) { return rn(6) == 0 ? rn(16) : rn(5); }     /* VI: mostly 0..4 */

static uint32_t rand_upper(void)
{
    uint32_t w, dest = 1 + rn(15);
    uint32_t ft = rreg(), fs = rreg(), fd = rreg();
    if (rn(3) == 0) dest = 15;
    if (rn(5) == 0) {
        w = 0x000002FFu;                         /* NOP */
    } else if (rn(2)) {                          /* op6 0x00..0x2F */
        uint32_t op6 = rn(0x30);
        w = dest << 21 | ft << 16 | fs << 11 | fd << 6 | op6;
    } else {                                     /* op11 0x00..0x2F */
        uint32_t op11 = rn(0x30);
        w = dest << 21 | ft << 16 | fs << 11 | (op11 >> 2) << 6 | 0x3C | (op11 & 3);
    }
    if (rn(60) == 0) w |= 0x40000000u;           /* E */
    if (rn(150) == 0) w |= 0x08000000u << rn(2); /* T / D */
    if (rn(30) == 0) w |= 0x20000000u;           /* M */
    if (rn(10) == 0) w |= 0x80000000u;           /* I: the lower word is LOI's value */
    return w;
}

static uint32_t rand_lower(void)
{
    static const uint8_t op7s[] = {0x00, 0x01, 0x04, 0x05, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13,
                                   0x14, 0x15, 0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C,
                                   0x20, 0x21, 0x24, 0x25, 0x28, 0x29, 0x2C, 0x2D, 0x2E, 0x2F};
    static const uint8_t op11s[] = {0x30, 0x31, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
                                    0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x64, 0x68,
                                    0x69, 0x6C, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x78,
                                    0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};
    static const uint8_t low6s[] = {0x30, 0x31, 0x32, 0x34, 0x35};
    uint32_t k = rn(10), w, dest = 1 + rn(15);
    if (rn(3) == 0) dest = 15;
    if (k < 2) return 0x8000033Cu;               /* NOP */
    if (k < 6) {
        uint32_t op7 = op7s[rn(sizeof op7s)];
        uint32_t ft = rn(16), fs = rn(16), imm;
        if (op7 <= 0x09 || (op7 >= 0x18 && op7 <= 0x2F)) { /* VI operands */
            if (op7 == 0x00 || op7 == 0x01) { ft = rreg() & 15; fs = rvi(); if (op7 == 1) { fs = rreg() & 15; ft = rvi(); } }
            else { ft = rvi(); fs = rvi(); }
        }
        imm = rnd() & 0x7FF;
        if (op7 >= 0x20) imm = (uint32_t)((int)rn(13) - 6) & 0x7FF; /* short branches */
        w = op7 << 25 | dest << 21 | ft << 16 | fs << 11 | imm;
        if (op7 >= 0x10 && op7 <= 0x13) w = op7 << 25 | (rnd() & 0xFFFFFF);
        if (op7 >= 0x10 && op7 <= 0x13 && rn(2)) w = op7 << 25 | (rnd() & 0x3FFFF);
        return w;
    }
    if (k < 8) {
        uint32_t low6 = low6s[rn(sizeof low6s)];
        return 0x80000000u | rvi() << 16 | rvi() << 11 | (low6 == 0x32 ? rn(32) : rvi()) << 6 | low6;
    }
    {
        uint32_t op11 = op11s[rn(sizeof op11s)];
        uint32_t ft = rreg() & 15, fs = rreg() & 15;
        /* integer operands of LQI/SQI/LQD/SQD/MTIR/MFIR/ILWR/ISWR/XTOP/XITOP/XGKICK */
        switch (op11) {
        case 0x34: case 0x36: fs = rvi(); break;
        case 0x35: case 0x37: ft = rvi(); break;
        case 0x3C: ft = rvi(); break;
        case 0x3D: fs = rvi(); break;
        case 0x3E: case 0x3F: ft = rvi(); fs = rvi(); break;
        case 0x68: case 0x69: ft = rvi(); break;
        case 0x6C: fs = rvi(); break;
        default: break;
        }
        return 0x80000000u | dest << 21 | ft << 16 | fs << 11 | (op11 >> 2) << 6 | 0x3C | (op11 & 3);
    }
}

/* a fresh VU1 state with random registers, flags and memory, and a random
 * program of *n pairs at 0 (then an E pair and its delay slot), loaded */
static void fuzz_setup(vu_state *A, uint32_t *code, uint32_t *n_out)
{
    uint32_t n = 8 + rn(120), k;
    int i;
    vu_init(A, 1);
    A->int_branch_quirk = rn(8) != 0;
    A->break_on_dt = rn(4) == 0;
    for (k = 1; k < 32; k++)
        for (i = 0; i < 4; i++) A->vf[k].u[i] = rfloat();
    for (i = 0; i < 4; i++) A->acc.u[i] = rfloat();
    for (k = 1; k < 16; k++) A->vi[k] = (uint16_t)(rn(4) ? rn(64) : rnd());
    A->q = rfloat(); A->p = rfloat(); A->i = rfloat(); A->r = 0x3F800000u | (rnd() & 0x7FFFFF);
    A->mac = rnd() & 0xFFFF; A->status = rnd() & 0xFFF; A->clip = rnd() & 0xFFFFFF;
    A->top = (uint16_t)rnd(); A->itop = (uint16_t)rnd();
    for (k = 0; k < sizeof A->mem / 4; k++) {
        uint32_t v = rn(3) ? rfloat() : rn(64);
        memcpy(A->mem + 4 * k, &v, 4);
    }
    if (rn(2)) { /* GIF tags that end soon, so XGKICK walks real packets */
        for (k = 0; k < 64; k++) {
            uint32_t tag = (1 + rn(3)) | (rn(3) ? 0x8000u : 0);
            memcpy(A->mem + 16 * k, &tag, 4);
            tag = (rn(3) << 26) | (rn(16) << 28);
            memcpy(A->mem + 16 * k + 4, &tag, 4);
        }
    }
    memset(code, 0, 2 * 2048 * 4);
    for (k = 0; k < n; k++) {
        uint32_t up = rand_upper(), lo = rand_lower();
        if (up & 0x80000000u) lo = rfloat();
        code[2 * k] = lo;
        code[2 * k + 1] = up;
    }
    code[2 * n] = 0x8000033Cu; code[2 * n + 1] = 0x400002FFu;
    code[2 * n + 2] = 0x8000033Cu; code[2 * n + 3] = 0x000002FFu;
    vu_load_code(A, 0, code, (n + 2) * 8);
    *n_out = n;
}

/* what to do after a vu_run call that stopped with s: 0 = stop the
 * iteration, 1 = carry on (the caller applies reload_at and reload_n, then
 * restart: 0 none, 1 MSCNT, 2 MSCAL at start_pc) */
static int fuzz_next(int s, uint32_t n, uint32_t *code, uint32_t *reload_at, uint32_t *reload_n,
                     int *restart, uint32_t *start_pc)
{
    *reload_n = 0;
    *restart = 0;
    if (s == VU_STOP_EBIT || s == VU_STOP_DBIT || s == VU_STOP_IDLE) {
        uint32_t r = rn(4), k;
        if (r == 0) return 0;
        if (r == 1) { /* re-upload a few pairs (some unchanged) */
            uint32_t at = rn(n), m = 1 + rn(4);
            for (k = at; k < at + m && k < n; k++)
                if (rn(2)) { code[2 * k] = rand_lower(); code[2 * k + 1] = rand_upper() & ~0x80000000u; }
            *reload_at = at;
            *reload_n = m;
        }
        if (s != VU_STOP_DBIT) {
            if (rn(2)) *restart = 1;
            else { *restart = 2; *start_pc = rn(n) * 8; }
        }
    }
    return 1;
}

static uint64_t fuzz_budget(void)
{
    static const uint64_t budgets[] = {3, 7, 20, 64, 300, 5000};
    return budgets[rn(6)];
}

#endif
