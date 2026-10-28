/* SPDX-License-Identifier: CC0-1.0 */
/* VIF command / UNPACK tests (ctest -L vu).  Expectations computed by hand. */
#include <stdlib.h>

#include "vif.h"
#include "vu_test.h"

int g_fail;
static vu_state V;
static vif_state X;
static int g_control;

#define VC(cmd, num, imm) (((uint32_t)(cmd) << 24) | ((uint32_t)(num) << 16) | ((uint32_t)(imm) & 0xFFFF))
/* UNPACK: vn 0..3 = S,V2,V3,V4; vl 0..3 = 32,16,8,5 */
#define UNPACK(m, vn, vl, num, addr, usn, flg) \
    VC(0x60 | ((m) << 4) | ((vn) << 2) | (vl), num, (addr) | ((usn) << 14) | ((flg) << 15))

static void fresh(int id)
{
    vif_free(&X);
    vu_init(&V, id);
    vif_init(&X, id, &V);
}

static uint32_t *M(uint32_t qw) { return (uint32_t *)(V.mem + qw * 16); }

static void feed(const uint32_t *w, size_t n) { CHECK(vif_write(&X, w, n) == n); }

#define CHECKQ(qw, a, b, c, d)                                               \
    do {                                                                     \
        CHECKX(M(qw)[0], a); CHECKX(M(qw)[1], b);                            \
        CHECKX(M(qw)[2], c); CHECKX(M(qw)[3], d);                            \
    } while (0)

static void t_unpack_s(void)
{
    const uint32_t w[] = {
        VC(0x01, 0, 0x0101),
        UNPACK(0, 0, 0, 2, 0, 0, 0), F(1.0f), F(2.0f),
        UNPACK(0, 0, 1, 2, 2, 0, 0), 0x00028001,
        UNPACK(0, 0, 1, 1, 4, 1, 0), 0x00008001,
        UNPACK(0, 0, 2, 3, 5, 0, 0), 0x00017F80,
    };
    fresh(1);
    feed(w, sizeof w / 4);
    CHECKQ(0, F(1), F(1), F(1), F(1));
    CHECKQ(1, F(2), F(2), F(2), F(2));
    CHECKQ(2, 0xFFFF8001, 0xFFFF8001, 0xFFFF8001, 0xFFFF8001);
    CHECKQ(3, 2, 2, 2, 2);
    CHECKQ(4, 0x8001, 0x8001, 0x8001, 0x8001);
    CHECKQ(5, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80, 0xFFFFFF80);
    CHECKQ(6, 0x7F, 0x7F, 0x7F, 0x7F);
    CHECKQ(7, 1, 1, 1, 1);
}

static void t_unpack_v2_v3(void)
{
    const uint32_t w[] = {
        UNPACK(0, 1, 0, 1, 0, 0, 0), 0xA, 0xB,
        UNPACK(0, 1, 1, 2, 1, 0, 0), 0x00020001, 0x00040003,
        UNPACK(0, 1, 2, 2, 3, 0, 0), 0x04FF0201,
        UNPACK(0, 2, 0, 2, 5, 0, 0), 1, 2, 3, 4, 5, 6,
        UNPACK(0, 2, 1, 1, 7, 0, 0), 0x00020001, 0x00070003,   /* 48 bits -> 2 words */
        UNPACK(0, 2, 2, 1, 8, 0, 0), 0x85FE0201,               /* 24 bits -> 1 word */
        VC(0x00, 0, 0) /* NOP proves the padding was consumed */
    };
    fresh(1);
    feed(w, sizeof w / 4);
    CHECKQ(0, 0xA, 0xB, 0xA, 0xB);
    CHECKQ(1, 1, 2, 1, 2);
    CHECKQ(2, 3, 4, 3, 4);
    CHECKQ(3, 1, 2, 1, 2);
    CHECKQ(4, 0xFFFFFFFF, 4, 0xFFFFFFFF, 4);
    /* V3 W = the next stream component (docs/VU.md "V3 W lane") */
    CHECKQ(5, 1, 2, 3, 4);
    CHECKQ(6, 4, 5, 6, UNPACK(0, 2, 1, 1, 7, 0, 0)); /* V3-32: past the payload */
    CHECKQ(7, 1, 2, 3, 7);                           /* V3-16: padding halfword */
    CHECKQ(8, 1, 2, 0xFFFFFFFE, 0xFFFFFF85);         /* V3-8 element 0: padding byte */
    CHECK(X.stats.cmds[0] == 1);
}

/* The V3 W lane as measured against PCSX2 (docs/VU.md "V3 W lane",
 * docs/VALIDATION.md section 5). */
static void t_unpack_v3_w(void)
{
    uint32_t w[64];
    int n = 0, k;
    uint32_t e;
    /* V3-16, NUM 17: 51 halfwords 0x100+k, then the padding halfword 0x8123 */
    w[n++] = UNPACK(0, 2, 1, 17, 0x10, 0, 0);
    for (k = 0; k < 26; k++) {
        uint32_t lo = 0x100u + 2u * (uint32_t)k, hi = lo + 1;
        if (k == 25) hi = 0x8123;
        w[n++] = lo | (hi << 16);
    }
    /* V3-16, NUM 2: 6 halfwords end on a word boundary -> W of element 1 is
     * the low half of the next stream word (the NOP after it) */
    w[n++] = UNPACK(0, 2, 1, 2, 0x30, 0, 0); w[n++] = 0x00020001; w[n++] = 0x00040003; w[n++] = 0x00060005;
    w[n++] = VC(0x00, 0, 0x8001);
    w[n++] = UNPACK(0, 2, 1, 2, 0x32, 1, 0); w[n++] = 0x00020001; w[n++] = 0x00040003; w[n++] = 0x00060005;
    w[n++] = VC(0x00, 0, 0x8001);
    /* V3-8, NUM 3: only element 0 takes the next byte, the others get 0 */
    w[n++] = UNPACK(0, 2, 2, 3, 0x38, 0, 0); w[n++] = 0x04030201; w[n++] = 0x08070605; w[n++] = 0x0C0B0A09;
    w[n++] = VC(0x00, 0, 0);
    fresh(1);
    for (e = 0; e < 0x40; e++) M(e)[3] = 0xDEAD;
    feed(w, (size_t)n);
    for (e = 0; e < 17; e++) {
        uint32_t want = (e % 16 == 7 || e % 16 == 9) ? 0 : (e == 16 ? 0xFFFF8123u : 0x100u + 3u * e + 3u);
        CHECKX(M(0x10 + e)[0], 0x100u + 3u * e);
        CHECKX(M(0x10 + e)[2], 0x100u + 3u * e + 2u);
        CHECKX(M(0x10 + e)[3], want);
    }
    CHECKQ(0x30, 1, 2, 3, 4);
    CHECKQ(0x31, 4, 5, 6, 0xFFFF8001);
    CHECKQ(0x33, 4, 5, 6, 0x8001);                   /* USN: zero-extended */
    CHECKQ(0x38, 1, 2, 3, 4);
    CHECKQ(0x39, 4, 5, 6, 0);
    CHECKQ(0x3A, 7, 8, 9, 0);
    CHECK(vif_idle(&X));
}

/* A V3 W lane past the payload waits for the next stream word when the
 * payload ends a vif_write call, and then goes through STMOD and the mask. */
static void t_unpack_v3_w_split(void)
{
    const uint32_t a[] = {
        VC(0x30, 0, 0), 0x10, 0x20, 0x30, 0x40,             /* STROW */
        VC(0x05, 0, 1),                                     /* STMOD offset */
        UNPACK(0, 2, 1, 2, 0x20, 0, 0), 0x00020001, 0x00040003, 0x00060005,
    };
    const uint32_t b[] = {VC(0x00, 0, 0x0100), VC(0x05, 0, 0)};
    const uint32_t c[] = {
        VC(0x20, 0, 0), 0xC0u << 8,                         /* cycle 1: W protected */
        VC(0x01, 0, 0x0201),                                /* CL 1, WL 2: filling */
        UNPACK(1, 2, 1, 4, 0x28, 0, 0), 0x00020001, 0x00040003, 0x00060005,
    };
    const uint32_t d[] = {VC(0x00, 0, 0x0042)};
    fresh(1);
    M(0x21)[3] = 0xDEAD;
    M(0x2A)[3] = 0xDEAD;
    M(0x2B)[3] = 0xBEEF;
    feed(a, sizeof a / 4);
    CHECKX(M(0x20)[3], 0x40 + 4);
    CHECKX(M(0x21)[0], 0x10 + 4);
    CHECKX(M(0x21)[3], 0xDEAD);                         /* waits for the next word */
    feed(b, sizeof b / 4);
    CHECKX(M(0x21)[3], 0x40 + 0x100);                   /* NOP's low half + ROW.w */
    /* NUM 4 with CL 1 / WL 2: elements 0, 1 at 0x28, 0x2A; fill cycles at
     * 0x29, 0x2B repeat them with W protected by the mask */
    feed(c, sizeof c / 4);
    CHECKX(M(0x28)[3], 4);
    CHECKX(M(0x2A)[0], 4);
    CHECKX(M(0x2B)[0], 4);
    CHECKX(M(0x2A)[3], 0xDEAD);
    CHECKX(M(0x2B)[3], 0xBEEF);
    feed(d, sizeof d / 4);
    CHECKX(M(0x2A)[3], 0x42);
    CHECKX(M(0x2B)[3], 0xBEEF);                         /* still protected */
    CHECK(vif_idle(&X));
}

static void t_unpack_v4(void)
{
    const uint32_t w[] = {
        UNPACK(0, 3, 0, 1, 0, 0, 0), 1, 2, 3, 4,
        UNPACK(0, 3, 1, 1, 1, 0, 0), 0x0001FFFF, 0x80000002,
        UNPACK(0, 3, 1, 1, 2, 1, 0), 0x0001FFFF, 0x80000002,
        UNPACK(0, 3, 2, 1, 3, 0, 0), 0x80FF0201,
        UNPACK(0, 3, 2, 1, 4, 1, 0), 0x80FF0201,
        UNPACK(0, 3, 3, 2, 5, 0, 0), 0x7FE0801F,
    };
    fresh(1);
    feed(w, sizeof w / 4);
    CHECKQ(0, 1, 2, 3, 4);
    CHECKQ(1, 0xFFFFFFFF, 1, 2, 0xFFFF8000);
    CHECKQ(2, 0xFFFF, 1, 2, 0x8000);
    CHECKQ(3, 1, 2, 0xFFFFFFFF, 0xFFFFFF80);
    CHECKQ(4, 1, 2, 0xFF, 0x80);
    if (g_control) CHECKQ(5, 0x1F, 0, 0, 1); /* control: forgets the <<3 / <<7 */
    else CHECKQ(5, 0xF8, 0, 0, 0x80);
    CHECKQ(6, 0, 0xF8, 0xF8, 0);
}

static void t_unpack_skip_fill(void)
{
    uint32_t w[64];
    int n = 0, k;
    fresh(1);
    /* skipping write: CL = 4, WL = 2 */
    w[n++] = VC(0x01, 0, (2 << 8) | 4);
    w[n++] = UNPACK(0, 3, 0, 4, 0x10, 0, 0);
    for (k = 0; k < 16; k++) w[n++] = 0x100 + k;
    /* filling write: CL = 1, WL = 3, rows 1 and 2 filled from ROW */
    w[n++] = VC(0x01, 0, (3 << 8) | 1);
    w[n++] = VC(0x30, 0, 0); w[n++] = 0x51; w[n++] = 0x52; w[n++] = 0x53; w[n++] = 0x54;
    w[n++] = VC(0x20, 0, 0); w[n++] = 0x00555500;
    w[n++] = UNPACK(1, 3, 0, 3, 0x20, 0, 0); /* 3 qwords written, 1 element read */
    w[n++] = 0xA; w[n++] = 0xB; w[n++] = 0xC; w[n++] = 0xD;
    w[n++] = VC(0x00, 0, 0);
    for (k = 0; k < 4; k++) { M(0x12)[k] = 0xEE; M(0x13)[k] = 0xEE; }
    feed(w, (size_t)n);
    CHECKQ(0x10, 0x100, 0x101, 0x102, 0x103);
    CHECKQ(0x11, 0x104, 0x105, 0x106, 0x107);
    CHECKQ(0x12, 0xEE, 0xEE, 0xEE, 0xEE);  /* skipped */
    CHECKQ(0x14, 0x108, 0x109, 0x10A, 0x10B);
    CHECKQ(0x15, 0x10C, 0x10D, 0x10E, 0x10F);
    CHECKQ(0x20, 0xA, 0xB, 0xC, 0xD);
    CHECKQ(0x21, 0x51, 0x52, 0x53, 0x54);
    CHECKQ(0x22, 0x51, 0x52, 0x53, 0x54);
    CHECK(X.stats.cmds[0] == 1);
    CHECKX(vif_payload_words(UNPACK(0, 3, 0, 3, 0, 0, 0), 1, 3), 4);
    CHECKX(vif_payload_words(UNPACK(0, 3, 0, 4, 0, 0, 0), 4, 2), 16);
    CHECKX(vif_payload_words(UNPACK(0, 3, 0, 7, 0, 0, 0), 2, 3), 4 * 5);
}

static void t_unpack_mask_mode(void)
{
    const uint32_t w[] = {
        VC(0x30, 0, 0), 0x10, 0x20, 0x30, 0x40,         /* STROW */
        VC(0x31, 0, 0), 0xA0, 0xB0, 0xC0, 0xD0,         /* STCOL */
        VC(0x20, 0, 0), 0xE4 | (0xE4u << 8),            /* row0: data,row,col,protect */
        UNPACK(1, 3, 0, 2, 0, 0, 0), 1, 2, 3, 4, 5, 6, 7, 8,
        VC(0x05, 0, 1),                                 /* STMOD offset */
        UNPACK(0, 3, 0, 1, 2, 0, 0), 1, 2, 3, 4,
        VC(0x05, 0, 2),                                 /* STMOD difference */
        UNPACK(0, 0, 0, 2, 3, 0, 0), 5, 7,
        VC(0x05, 0, 0),
        VC(0x01, 0, 0x0404),                            /* CL = WL = 4 */
        UNPACK(1, 3, 0, 2, 8, 0, 0), 1, 2, 3, 4, 5, 6, 7, 8,
    };
    fresh(1);
    M(0)[3] = 0xDEAD;
    M(1)[3] = 0xBEEF;
    feed(w, sizeof w / 4);
    CHECKQ(0, 1, 0x20, 0xA0, 0xDEAD);
    CHECKQ(1, 5, 0x20, 0xA0, 0xBEEF);  /* CL = WL = 1: every qword is write cycle 0 */
    CHECKQ(2, 0x11, 0x22, 0x33, 0x44);
    CHECKQ(3, 0x15, 0x25, 0x35, 0x45);
    CHECKQ(4, 0x1C, 0x2C, 0x3C, 0x4C);
    CHECKX(X.row[0], 0x1C);
    CHECKQ(8, 1, 0x2C, 0xA0, 0);  /* ROW after the difference-mode unpack */
    CHECKQ(9, 5, 0x2C, 0xB0, 0);                        /* write cycle 1: COL[1] */
}

static void t_tops_double_buffer(void)
{
    /* program: xtop vi1 ; xitop vi2 ; sq vi.. -> isw x of TOP to qw 0x3F0 */
    const uint32_t prog[] = {
        XTOP(1), UNOP,
        XITOP(2), UNOP,
        LNOP, UNOP,
        ISW(DX, 1, 2, 0x10), UNOP | U_E,
        LNOP, UNOP,
        LNOP, UNOP | U_E,   /* MSCNT lands here (TPC) */
        LNOP, UNOP,
    };
    uint32_t w[64];
    int n = 0, k;
    fresh(1);
    w[n++] = VC(0x00, 0, 0);
    w[n++] = VC(0x4A, 7, 0);
    for (k = 0; k < 14; k++) w[n++] = prog[k];
    w[n++] = VC(0x03, 0, 0x100);           /* BASE */
    w[n++] = VC(0x02, 0, 0x080);           /* OFFSET: DBF=0, TOPS=BASE */
    w[n++] = VC(0x04, 0, 0x30);            /* ITOP */
    w[n++] = UNPACK(0, 0, 0, 1, 2, 0, 1);  /* FLG: TOPS + 2 */
    w[n++] = 0x111;
    w[n++] = VC(0x14, 0, 0);               /* MSCAL 0 */
    w[n++] = UNPACK(0, 0, 0, 1, 2, 0, 1);
    w[n++] = 0x222;
    w[n++] = VC(0x04, 0, 0x31);
    w[n++] = VC(0x15, 0, 0);               /* MSCALF 0 */
    w[n++] = VC(0x17, 0, 0);               /* MSCNT: continues at TPC (end) */
    feed(w, (size_t)n);
    CHECKX(M(0x102)[0], 0x111);
    CHECKX(M(0x182)[0], 0x222);
    CHECKX(V.vi[1], 0x180);                /* second MSCAL: TOP = BASE + OFFSET */
    CHECKX(M(0x30 + 0x10)[0], 0x100);      /* first run stored TOP at ITOP+0x10 */
    CHECKX(M(0x31 + 0x10)[0], 0x180);
    CHECKX(X.tops, 0x180);                 /* after 3 starts DBF = 1 */
    CHECK(X.stats.mscal == 3);
    CHECK(X.stats.mpg_bytes == 56);
    CHECK(X.stats.vu_runaways == 0);
}

static uint8_t g_out[4096];
static uint32_t g_out_n, g_out_calls;
static void gif_sink(void *u, const uint8_t *d, uint32_t n)
{
    (void)u;
    if (g_out_n + n <= sizeof g_out) memcpy(g_out + g_out_n, d, n);
    g_out_n += n;
    g_out_calls++;
}
static void kick_sink(void *u, const uint8_t *d, uint32_t n, uint32_t a)
{
    (void)a;
    gif_sink(u, d, n);
}

static void t_direct_and_kick(void)
{
    /* MPG a program that XGKICKs qw 0, UNPACK a GIF packet there, MSCAL;
     * then DIRECT one packet to PATH2. */
    const uint32_t prog[] = {
        XGKICK(0), UNOP | U_E,
        LNOP, UNOP,
    };
    uint32_t w[64];
    int n = 0, k;
    fresh(1);
    V.gif_sink = kick_sink;
    X.gif_sink = gif_sink;
    g_out_n = g_out_calls = 0;
    w[n++] = VC(0x00, 0, 0);
    w[n++] = VC(0x4A, 2, 0);
    for (k = 0; k < 4; k++) w[n++] = prog[k];
    w[n++] = UNPACK(0, 3, 0, 2, 0, 0, 0);
    w[n++] = 0x8001; w[n++] = 0x10000000; w[n++] = 0xE; w[n++] = 0; /* PACKED 1x1 EOP */
    w[n++] = 0x11; w[n++] = 0x22; w[n++] = 0x33; w[n++] = 0x44;
    w[n++] = VC(0x14, 0, 0);
    w[n++] = VC(0x00, 0, 0);
    w[n++] = VC(0x00, 0, 0);
    w[n++] = VC(0x50, 0, 1);
    w[n++] = 0x8000; w[n++] = 0x20000000; w[n++] = 0; w[n++] = 0;
    feed(w, (size_t)n);
    CHECK(g_out_calls == 2);
    CHECKX(g_out_n, 32 + 16);
    CHECKX(((uint32_t *)g_out)[0], 0x8001);
    CHECKX(((uint32_t *)g_out)[4], 0x11);
    CHECKX(((uint32_t *)g_out)[9], 0x20000000);
    CHECK(X.stats.direct_bytes == 16);
}

static void t_split_stream(void)
{
    /* the same stream fed whole and one word at a time must agree */
    uint32_t w[256];
    int n = 0, k;
    uint8_t mem1[0x4000], code1[0x4000];
    w[n++] = VC(0x01, 0, 0x0101);
    w[n++] = VC(0x30, 0, 0); w[n++] = 1; w[n++] = 2; w[n++] = 3; w[n++] = 4;
    w[n++] = VC(0x20, 0, 0); w[n++] = 0x0000005C;
    w[n++] = UNPACK(1, 2, 1, 5, 0x40, 0, 0);
    for (k = 0; k < 8; k++) w[n++] = 0x00010002u * (uint32_t)(k + 1);
    w[n++] = VC(0x00, 0, 0);
    w[n++] = VC(0x4A, 3, 0x10);
    for (k = 0; k < 6; k++) w[n++] = (k & 1) ? UNOP : LNOP;
    w[n++] = UNPACK(0, 3, 3, 3, 0x50, 0, 0); w[n++] = 0x12345678; w[n++] = 0x9ABC;
    /* V3-16 whose last W is the next stream word (deferred when split) */
    w[n++] = UNPACK(0, 2, 1, 2, 0x60, 0, 0); w[n++] = 0x00020001; w[n++] = 0x00040003; w[n++] = 0x00060005;
    w[n++] = VC(0x00, 0, 0x7777);
    fresh(1);
    feed(w, (size_t)n);
    memcpy(mem1, V.mem, sizeof mem1);
    memcpy(code1, V.code, sizeof code1);
    fresh(1);
    for (k = 0; k < n; k++) feed(&w[k], 1);
    CHECK(memcmp(mem1, V.mem, sizeof mem1) == 0);
    CHECK(memcmp(code1, V.code, sizeof code1) == 0);
    CHECK(vif_idle(&X));
    CHECKX(M(0x40)[0], 2);              /* V3-16, x from data */
    CHECKX(M(0x40)[3], 4);              /* mask row0 w = 1 -> ROW.w */
    CHECKX(M(0x61)[3], 0x7777);         /* V3 W from the following NOP */
}

static void t_irq_stall(void)
{
    const uint32_t w[] = {VC(0x07, 0, 0x1234), VC(0x00, 0, 0) | 0x80000000u, VC(0x07, 0, 0x5678)};
    size_t used;
    fresh(1);
    X.stall_on_irq = 1;
    used = vif_write(&X, w, 3);
    CHECK(used == 2);
    CHECK(X.irq);
    CHECKX(X.mark, 0x1234);
    X.irq = 0;
    CHECK(vif_write(&X, w + used, 3 - used) == 1);
    CHECKX(X.mark, 0x5678);
}

static void t_vif0(void)
{
    const uint32_t w[] = {VC(0x02, 0, 4), VC(0x50, 0, 1), 1, 2, 3, 4,
                          UNPACK(0, 0, 0, 1, 0x1FF, 0, 0), 9};
    fresh(0);
    feed(w, sizeof w / 4);
    CHECK(X.stats.invalid_cmds == 2);   /* OFFSET and DIRECT are VIF1-only */
    CHECKX(M(0xFF)[0], 9);              /* VIF0 address field is 8 bits */
    CHECKX(vif_payload_words(VC(0x4A, 0, 0), 1, 1), 512);
    CHECKX(vif_payload_words(VC(0x50, 0, 0), 1, 1), 262144);
    CHECKX(vif_payload_words(VC(0x63, 0, 0), 1, 1), -1); /* S-5 does not exist */
}

typedef struct { const char *name; void (*fn)(void); } test_t;
static const test_t k_tests[] = {
    {"unpack_s", t_unpack_s},
    {"unpack_v2_v3", t_unpack_v2_v3},
    {"unpack_v3_w", t_unpack_v3_w},
    {"unpack_v3_w_split", t_unpack_v3_w_split},
    {"unpack_v4", t_unpack_v4},
    {"unpack_skip_fill", t_unpack_skip_fill},
    {"unpack_mask_mode", t_unpack_mask_mode},
    {"tops_double_buffer", t_tops_double_buffer},
    {"direct_and_kick", t_direct_and_kick},
    {"split_stream", t_split_stream},
    {"irq_stall", t_irq_stall},
    {"vif0", t_vif0},
};

int main(int argc, char **argv)
{
    unsigned i;
    int ran = 0;
    const char *want = argc > 1 ? argv[1] : NULL;
    if (want && !strcmp(want, "unpack_v4_control")) {
        g_control = 1;
        want = "unpack_v4";
    }
    for (i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        int before = g_fail;
        if (want && strcmp(want, k_tests[i].name)) continue;
        k_tests[i].fn();
        printf("%s %s\n", g_fail == before ? "ok  " : "FAIL", k_tests[i].name);
        ran++;
    }
    vif_free(&X);
    if (!ran) { printf("no test named %s\n", want); return 2; }
    return g_fail ? 1 : 0;
}
