/* SPDX-License-Identifier: CC0-1.0 */
/* The model program's constant block from the game's packet builders
 * (nr_const.h, docs/NATIVE-RENDER.md "Constants from the game"). */
#include "nr_const.h"
#include "nr_mem.h"

#include <math.h>
#include <string.h>

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

enum {
    E_TAG = -1, E_CMD = -2, E_UNPACK = -3, E_FLG = -4, E_CYCLE = -5, E_MSCAL = -6, E_ADDR = -7, E_CUT = -8,
    E_STMOD = -9
};

const char *nr_const_err(int code)
{
    switch (code) {
    case 0: return "ok";
    case E_TAG: return "DMA chain not walkable";
    case E_CMD: return "unexpected VIF command";
    case E_UNPACK: return "UNPACK other than V4-32 / masked";
    case E_FLG: return "UNPACK relative to TOPS (FLG)";
    case E_CYCLE: return "STCYCL CL != WL";
    case E_MSCAL: return "MSCAL other than 0";
    case E_ADDR: return "UNPACK outside the constant block and bone rows";
    case E_CUT: return "VIF command cut off at the end of the packet";
    case E_STMOD: return "STMOD != 0";
    default: return "?";
    }
}

/* ---- the VU1 program at address 0 (MSCAL 0) --------------------------------
 * Transcribed from the program the game uploads to VU1 address 0 (listing:
 * docs/NATIVE-RENDER.md).  vf = rows: R0..R3 = qw60..63 (object matrix),
 * V = qw24..27 (view, columns), P1 = qw4..7, P2 = qw8..11 (projection and clip,
 * columns), L = qw30..32 (light directions, columns).  The accumulation order
 * is the program's (x, y, z, w). */
/* VU FMAC arithmetic: computed in double, chopped toward zero to a single;
 * results below 2^-126 flush to zero (MADD = chop(acc + chop(a * b))).  The
 * VU's exponent-255 range does not occur in these matrices. */
static inline float vchop(double v)
{
    float f = (float)v;
    uint32_t u;
    memcpy(&u, &f, 4);
    if ((double)fabsf(f) > fabs(v)) u -= 1;          /* one ulp toward zero (f is not 0 here) */
    if ((u & 0x7F800000u) == 0) u &= 0x80000000u;    /* below 2^-126: flush to (signed) zero */
    memcpy(&f, &u, 4);
    return f;
}
static float vmul(float a, float b) { return vchop((double)a * (double)b); }
static float vadd(float a, float b) { return vchop((double)a + (double)b); }

static void mulv(float o[4], const nr_qw *cols, const float x[4])
{
    int k;
    for (k = 0; k < 4; k++) {
        float a = vmul(cols[0].f[k], x[0]);
        a = vadd(a, vmul(cols[1].f[k], x[1]));
        a = vadd(a, vmul(cols[2].f[k], x[2]));
        o[k] = vadd(a, vmul(cols[3].f[k], x[3]));
    }
}

void nr_const_prog0(nr_cblock *b)
{
    nr_qw *c = b->c;
    float vr[4][4], t[4];
    int i, k;
    for (i = 0; i < 4; i++) {
        mulv(vr[i], &c[24], c[60 + i].f);             /* V * Ri */
        mulv(t, &c[4], vr[i]);                        /* P1 * V * Ri -> 68 + i */
        memcpy(c[68 + i].f, t, 16);
        mulv(t, &c[8], vr[i]);                        /* P2 * V * Ri -> 72 + i */
        memcpy(c[72 + i].f, t, 16);
    }
    for (i = 0; i < 3; i++) {
        const float *r = c[60 + i].f;
        double s = (double)r[0] * r[0] + (double)r[1] * r[1] + (double)r[2] * r[2];
        float rl = s > 0.0 ? vchop(1.0 / sqrt(s)) : 0.0f;   /* ERLENG (EFU: double, chopped) */
        c[64 + i].f[0] = vmul(r[0], rl);
        c[64 + i].f[1] = vmul(r[1], rl);
        c[64 + i].f[2] = vmul(r[2], rl);
        c[64 + i].f[3] = r[3];
    }
    for (i = 0; i < 3; i++) {
        const float *n = c[64 + i].f;
        for (k = 0; k < 4; k++) {
            float a = vmul(c[30].f[k], n[0]);
            a = vadd(a, vmul(c[31].f[k], n[1]));
            c[100 + i].f[k] = vadd(a, vmul(c[32].f[k], n[2]));
        }
    }
    {
        /* sign of (R0 x R1) . R2: the MAC S flag of x after addy/addz */
        const float *r0 = c[60].f, *r1 = c[61].f, *r2 = c[62].f;
        float x = vmul(vadd(vmul(r0[1], r1[2]), -vmul(r0[2], r1[1])), r2[0]);
        float y = vmul(vadd(vmul(r0[2], r1[0]), -vmul(r0[0], r1[2])), r2[1]);
        float z = vmul(vadd(vmul(r0[0], r1[1]), -vmul(r0[1], r1[0])), r2[2]);
        float d = vadd(vadd(x, y), z);
        c[111].f[2] = d < 0.0f ? -1.0f : 1.0f;
    }
    for (i = 64; i <= 75; i++) b->wr[i] = 1;
    b->wr[67] = 0;
    for (i = 100; i <= 102; i++) b->wr[i] = 1;
    b->wr[111] = 1;
}

/* ---- VIF word stream (the builders' subset) ------------------------------ */
typedef struct vs {
    nr_cblock *b;
    uint32_t cl, wl;
    uint32_t pend_cmd, pend_words, pend_got;
    uint32_t pay[256 * 4];
    int err;
} vs;

static void unpack(vs *s, uint32_t code)
{
    uint32_t num = (code >> 16) & 0xFF, imm = code & 0xFFFF, n = num ? num : 256, addr = imm & 0x3FF, e;
    if (imm & 0x8000) { s->err = E_FLG; return; }
    for (e = 0; e < n; e++) {
        uint32_t a = addr + e;
        if (a < NRQ_CONST_N) {
            memcpy(s->b->c[a].u, &s->pay[e * 4], 16);
            s->b->wr[a] = 1;
        } else if (a >= NR_BONE_ROW0 && a < NR_BONE_ROW0 + NR_BONE_ROWS) {
            memcpy(s->b->bones[a - NR_BONE_ROW0].u, &s->pay[e * 4], 16);
            if (a - NR_BONE_ROW0 + 1 > s->b->bones_hi) s->b->bones_hi = a - NR_BONE_ROW0 + 1;
        } else {
            s->err = E_ADDR;
            return;
        }
    }
}

static void exec(vs *s, uint32_t code)
{
    uint32_t cmd = (code >> 24) & 0x7F;
    if (cmd >= 0x60) {
        if (cmd != 0x6C) { s->err = E_UNPACK; return; }
        if (s->cl != s->wl) { s->err = E_CYCLE; return; }
        unpack(s, code);
        return;
    }
    switch (cmd) {
    case 0x00: case 0x02: case 0x03: case 0x04: case 0x06: case 0x07:
    case 0x10: case 0x11: case 0x13:
    case 0x20: case 0x30: case 0x31: case 0x50: case 0x51:
        return;      /* NOP OFFSET BASE ITOP MSKPATH3 MARK FLUSH* STMASK STROW STCOL DIRECT(HL): no constants */
    case 0x01: s->cl = code & 0xFF; s->wl = (code >> 8) & 0xFF; return;
    case 0x05: if (code & 3) s->err = E_STMOD; return;
    case 0x14: if (code & 0xFFFF) { s->err = E_MSCAL; return; } nr_const_prog0(s->b); return;
    default: s->err = E_CMD; return;          /* MSCALF MSCNT MPG other */
    }
}

static long payload_words(uint32_t code)
{
    uint32_t cmd = (code >> 24) & 0x7F, num = (code >> 16) & 0xFF, imm = code & 0xFFFF;
    if (cmd == 0x20) return 1;
    if (cmd == 0x30 || cmd == 0x31) return 4;
    if (cmd == 0x4A) return (long)(num ? num : 256) * 2;
    if (cmd == 0x50 || cmd == 0x51) return (long)(imm ? imm : 65536) * 4;
    if (cmd == 0x6C) return (long)(num ? num : 256) * 4;
    if (cmd >= 0x60) return -1;
    return 0;
}

static void feed(vs *s, uint32_t w)
{
    long n;
    if (s->err) return;
    if (s->pend_words) {
        uint32_t cmd = (s->pend_cmd >> 24) & 0x7F;
        if (cmd == 0x6C) s->pay[s->pend_got] = w;     /* only UNPACK payload is kept */
        if (++s->pend_got == s->pend_words) {
            s->pend_words = 0;
            exec(s, s->pend_cmd);
        }
        return;
    }
    n = payload_words(w);
    if (n < 0) { s->err = E_UNPACK; return; }
    if (n == 0) { exec(s, w); return; }
    s->pend_cmd = w;
    s->pend_words = (uint32_t)n;
    s->pend_got = 0;
}

/* readable game memory, not a poisoned (dead) packet (nr_mem.h) */
static const uint8_t *host(uint32_t a, uint32_t bytes)
{
    const uint8_t *p = nr_game_ptr(a, bytes ? bytes : 16);
    if (p && nr_poison_check(p, "nr_const", a)) return NULL;
    return p;
}

static void feed_blk(vs *s, const uint8_t *t, const uint8_t *data, uint32_t qwc)
{
    uint32_t i;
    feed(s, rd32(t + 8));
    feed(s, rd32(t + 12));
    if (data)
        for (i = 0; i < qwc * 4 && !s->err; i++) feed(s, rd32(data + 4 * i));
}

int nr_const_apply(nr_cblock *b, uint32_t pkt)
{
    vs s;
    uint32_t tadr = pkt, stack[4], sp = 0, tags = 0;
    s.b = b;
    s.cl = s.wl = 1;
    s.pend_words = s.pend_got = s.pend_cmd = 0;
    s.err = 0;
    for (;;) {
        const uint8_t *t = host(tadr, 16);
        uint32_t lo, hi, qwc, id;
        if (!t || ++tags > 256) return E_TAG;
        lo = rd32(t); hi = rd32(t + 4);
        qwc = lo & 0xFFFF; id = (lo >> 28) & 7;
        if (qwc && id != 0 && id != 3 && id != 4 && !nr_game_ptr(tadr, 16 + qwc * 16)) return E_TAG;   /* inline payload */
        switch (id) {
        case 1: feed_blk(&s, t, t + 16, qwc); tadr += 16 + qwc * 16; break;               /* CNT */
        case 2: feed_blk(&s, t, t + 16, qwc); tadr = hi; break;                            /* NEXT */
        case 3: case 4: {                                                                  /* REF(S) */
            const uint8_t *d = qwc ? host(hi, qwc * 16) : NULL;
            if (qwc && !d) return E_TAG;
            feed_blk(&s, t, d, qwc); tadr += 16; break;
        }
        case 0: {                                                                          /* REFE */
            const uint8_t *d = qwc ? host(hi, qwc * 16) : NULL;
            if (qwc && !d) return E_TAG;
            feed_blk(&s, t, d, qwc);
            goto done;
        }
        case 5:                                                                            /* CALL */
            feed_blk(&s, t, t + 16, qwc);
            if (sp >= 4) return E_TAG;
            stack[sp++] = tadr + 16 + qwc * 16; tadr = hi; break;
        case 6:                                                                            /* RET */
            feed_blk(&s, t, t + 16, qwc);
            if (sp == 0) goto done;
            tadr = stack[--sp]; break;
        default:                                                                           /* END */
            feed_blk(&s, t, t + 16, qwc);
            goto done;
        }
        if (s.err) return s.err;
    }
done:
    if (s.err) return s.err;
    if (s.pend_words) return E_CUT;
    return 0;
}

uint32_t nr_const_inline_bytes(uint32_t pkt, uint32_t max_bytes)
{
    const uint8_t *t = host(pkt, 16);
    uint32_t lo, id, bytes;
    if (!t) return 0;
    lo = rd32(t);
    id = (lo >> 28) & 7;
    bytes = 16u + (lo & 0xFFFFu) * 16u;
    if ((id != 6 && id != 7) || bytes > max_bytes) return 0;   /* RET / END with the payload inline only */
    if (!nr_game_ptr(pkt, bytes)) return 0;
    return bytes;
}

int nr_const_apply_inline(nr_cblock *b, const void *copy, uint32_t bytes)
{
    const uint8_t *t = (const uint8_t *)copy;
    uint32_t lo, qwc, id;
    vs s;
    if (!t || bytes < 16) return E_TAG;
    lo = rd32(t);
    qwc = lo & 0xFFFF; id = (lo >> 28) & 7;
    if ((id != 6 && id != 7) || 16u + qwc * 16u > bytes) return E_TAG;
    s.b = b;
    s.cl = s.wl = 1;
    s.pend_words = s.pend_got = s.pend_cmd = 0;
    s.err = 0;
    feed_blk(&s, t, t + 16, qwc);   /* = nr_const_apply on the same packet: RET at depth 0 / END ends it */
    if (s.err) return s.err;
    if (s.pend_words) return E_CUT;
    return 0;
}
