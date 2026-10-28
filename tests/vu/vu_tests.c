/* SPDX-License-Identifier: CC0-1.0 */
/* VU instruction unit tests (ctest -L vu).  Every expectation is computed by
 * hand from the instruction definitions; see docs/VU.md. */
#include <stdlib.h>

#include "vu_decode.h"
#include "vu_test.h"

int g_fail;
static vu_state V;
static int g_control; /* set for the deliberately-wrong control variants */

static void fresh(void)
{
    vu_init(&V, 1);
}

/* ---------------------------------------------------------------- decode */

static void t_decode_retail(void)
{
    /* words copied from the retail microcode (packet 0x436CB0 / 0x4371D0) */
    static const struct { uint32_t lw, uw; const char *up, *lo; } k[] = {
        {0x8000033C, 0x400002FF, "nop[e]", "nop"},
        {0x090A004C, 0x000002FF, "nop", "ilw.x vi10, 76(vi00)"},
        {0x00E10056, 0x000002FF, "nop", "lq.yzw vf01, 86(vi00)"},
        {0x800906BC, 0x000002FF, "nop", "xtop vi09"},
        {0x806503BC, 0x018531AA, "mul.xy vf06, vf06, vf05", "div Q, vf00w, vf05x"},
        {0x3F7FBE77, 0x800002FF, "nop[i]", "loi 0x3f7fbe77 (0.999)"},
        {0x8000033C, 0x01800162, "addi.xy vf05, vf00, I", "nop"},
        {0x4A0F1800, 0x000002FF, "nop", "jalr vi15, vi03"},
        {0x2403FFFF, 0x000002FF, "nop", "fcand vi01, 0x03ffff"},
        {0x8000033C, 0x01C109FF, "clipw.xyz vf01, vf01w", "nop"},
        {0x8000033C, 0x01E139BC, "mulax.xyzw acc, vf07, vf01x", "nop"},
        {0x8000033C, 0x01E0404B, "maddw.xyzw vf01, vf08, vf00w", "nop"},
        {0x30073800, 0x01C0839C, "mulq.xyz vf14, vf16, Q", "fmeq vi07, vi07"},
        {0x50042817, 0x01D37BEE, "opmsub.xyz vf15, vf15, vf19", "ibeq vi04, vi05, 0x1f78"},
        {0x03E4A7FC, 0x01CF9AFE, "opmula.xyz acc, vf19, vf15", "sq.xyzw vf20, -4(vi04)"},
        {0x10021001, 0x01F4097D, "ftoi4.xyzw vf20, vf01", "iaddiu vi02, vi02, 0x1"},
        {0x800217F2, 0x01E2106B, "max.xyzw vf01, vf02, vf02", "iaddi vi02, vi02, -1"},
        {0x80022974, 0x000002FF, "nop", "iand vi05, vi05, vi02"},
    };
    unsigned i;
    for (i = 0; i < sizeof k / sizeof k[0]; i++) {
        vu_pair p;
        char buf[160], want[160];
        vu_decode_pair(k[i].lw, k[i].uw, &p);
        vu_disasm_pair(&p, 0x1EB8, buf, sizeof buf); /* the branch sits at 0x1EB8 */
        snprintf(want, sizeof want, "%-44s %s", k[i].up, k[i].lo);
        if (strcmp(buf, want) != 0) {
            printf("FAIL decode %08X %08X:\n  got  '%s'\n  want '%s'\n", k[i].uw, k[i].lw, buf, want);
            g_fail++;
        }
    }
    /* encoder used by these tests == decoder */
    {
        vu_pair p;
        vu_decode_pair(DIV(0, 3, 5, 0), UNOP, &p);
        CHECKX(DIV(0, 3, 5, 0), 0x806503BC); /* retail word */
        CHECK(p.lo.op == VU_L_DIV && p.lo.fs == 0 && p.lo.fsf == 3 && p.lo.ft == 5 && p.lo.ftf == 0);
        vu_decode_pair(IADDIU(3, 2, 0x7FFF), UNOP, &p);
        CHECK(p.lo.op == VU_L_IADDIU && p.lo.imm == 0x7FFF && p.lo.ft == 3 && p.lo.fs == 2);
        vu_decode_pair(FSAND(4, 0xFC0), UNOP, &p);
        CHECK(p.lo.op == VU_L_FSAND && p.lo.imm == 0xFC0 && p.lo.ft == 4);
    }
}

/* ---------------------------------------------------------------- FMAC */

static void t_arith(void)
{
    const pair_t p[] = {
        {ADD(DXYZW, 3, 1, 2), LNOP},
        {SUB(DX | DZ, 4, 1, 2), LNOP},
        {MULbc(DXYZW, 5, 1, 2, 1), LNOP},
        {MULA(DXYZW, 1, 2), LNOP},
        {MADDbc(DXYZW, 6, 1, 2, 0), LNOP},
        {MSUB(DXYZW, 7, 1, 2), LNOP},
        {MULi(DXYZW, 8, 1), LNOP},
        {ADDq(DXYZW, 9, 1), LNOP},
        {MAX(DXYZW, 10, 1, 2), LNOP},
        {MINIbc(DXYZW, 11, 1, 2, 1), LNOP},
        {MAXi(DXYZW, 12, 1), LNOP},
        {MINIi(DXYZW, 13, 1), LNOP},
        {ADDbc(DW, 14, 1, 2, 3), LNOP},
        {ABS(DXYZW, 15, 1), LNOP},
    };
    fresh();
    setv(&V, 1, 1.5f, 2.25f, -3.0f, 4.0f);
    setv(&V, 2, 2.25f, 0.5f, 3.0f, -8.0f);
    setv(&V, 4, 9, 9, 9, 9);
    setv(&V, 14, 9, 9, 9, 9);
    V.i = F(2.0f);
    V.q = F(0.25f);
    CHECK(run_prog(&V, p, (int)(sizeof p / sizeof p[0])) == VU_STOP_EBIT);
    CHECKV(&V, 3, 3.75f, 2.75f, 0.0f, -4.0f);
    CHECKV(&V, 4, -0.75f, 9.0f, -6.0f, 9.0f);
    CHECKV(&V, 5, 0.75f, 1.125f, -1.5f, 2.0f);
    CHECKV(&V, 6, 6.75f, 6.1875f, -15.75f, -23.0f);
    CHECKV(&V, 7, 0.0f, 0.0f, 0.0f, 0.0f);
    CHECKV(&V, 8, 3.0f, 4.5f, -6.0f, 8.0f);
    CHECKV(&V, 9, 1.75f, 2.5f, -2.75f, 4.25f);
    CHECKV(&V, 10, 2.25f, 2.25f, 3.0f, 4.0f);
    CHECKV(&V, 11, 0.5f, 0.5f, -3.0f, 0.5f);
    CHECKV(&V, 12, 2.0f, 2.25f, 2.0f, 4.0f);
    CHECKV(&V, 13, 1.5f, 2.0f, -3.0f, 2.0f);
    CHECKV(&V, 14, 9.0f, 9.0f, 9.0f, -4.0f);
    CHECKV(&V, 15, 1.5f, 2.25f, 3.0f, 4.0f);
    CHECKV(&V, 0, 0.0f, 0.0f, 0.0f, 1.0f);
    /* ACC holds MULA's product */
    CHECKX(V.acc.u[0], F(3.375f));
    CHECKX(V.acc.u[3], F(-32.0f));
    /* last FMAC flag writer was ADDbc.w (-4): S flag on w only; MSUB was all-zero */
    CHECKX(V.mac, 0x0010);
    CHECKX(V.status & 0xF, VU_ST_S);
    CHECK(V.status & VU_ST_ZS); /* sticky Z from ADD.z / MSUB */
    CHECK(V.status & VU_ST_SS);
}

/* every remaining FMAC form the retail code uses (and the rest of the family),
 * one instruction per run: a = vf1, b = vf2, ACC = (10,20,30,40), I = 2, Q = 1/4 */
static void t_acc_forms(void)
{
    static const struct { const char *name; uint32_t up; int to_acc; float r[4]; } k[] = {
        {"ADDA", UP2(0x28, DXYZW, 2, 1), 1, {3.75f, 2.75f, 0, -4}},
        {"SUBA", UP2(0x2C, DXYZW, 2, 1), 1, {-0.75f, 1.75f, -6, 12}},
        {"MADDA", UP2(0x29, DXYZW, 2, 1), 1, {13.375f, 21.125f, 21, 8}},
        {"MSUBA", UP2(0x2D, DXYZW, 2, 1), 1, {6.625f, 18.875f, 39, 72}},
        {"ADDAw", UP2(0x03, DXYZW, 2, 1), 1, {-6.5f, -5.75f, -11, -4}},
        {"SUBAx", UP2(0x04, DXYZW, 2, 1), 1, {-0.75f, 0, -5.25f, 1.75f}},
        {"MADDAy", UP2(0x09, DXYZW, 2, 1), 1, {10.75f, 21.125f, 28.5f, 42}},
        {"MSUBAz", UP2(0x0E, DXYZW, 2, 1), 1, {5.5f, 13.25f, 39, 28}},
        {"MULAy", UP2(0x19, DXYZW, 2, 1), 1, {0.75f, 1.125f, -1.5f, 2}},
        {"MADD", UP(0x29, DXYZW, 2, 1, 3), 0, {13.375f, 21.125f, 21, 8}},
        {"MULAi", UP2(0x1E, DXYZW, 0, 1), 1, {3, 4.5f, -6, 8}},
        {"ADDAi", UP2(0x22, DXYZW, 0, 1), 1, {3.5f, 4.25f, -1, 6}},
        {"SUBAi", UP2(0x26, DXYZW, 0, 1), 1, {-0.5f, 0.25f, -5, 2}},
        {"MADDAi", UP2(0x23, DXYZW, 0, 1), 1, {13, 24.5f, 24, 48}},
        {"MSUBAi", UP2(0x27, DXYZW, 0, 1), 1, {7, 15.5f, 36, 32}},
        {"MULAq", UP2(0x1C, DXYZW, 0, 1), 1, {0.375f, 0.5625f, -0.75f, 1}},
        {"ADDAq", UP2(0x20, DXYZW, 0, 1), 1, {1.75f, 2.5f, -2.75f, 4.25f}},
        {"SUBAq", UP2(0x24, DXYZW, 0, 1), 1, {1.25f, 2, -3.25f, 3.75f}},
        {"MADDAq", UP2(0x21, DXYZW, 0, 1), 1, {10.375f, 20.5625f, 29.25f, 41}},
        {"MSUBAq", UP2(0x25, DXYZW, 0, 1), 1, {9.625f, 19.4375f, 30.75f, 39}},
        {"MSUBx", UP(0x0C, DXYZW, 2, 1, 3), 0, {6.625f, 14.9375f, 36.75f, 31}},
        {"MADDi", UP(0x23, DXYZW, 0, 1, 3), 0, {13, 24.5f, 24, 48}},
        {"MSUBi", UP(0x27, DXYZW, 0, 1, 3), 0, {7, 15.5f, 36, 32}},
        {"SUBy", UP(0x05, DXYZW, 2, 1, 3), 0, {1, 1.75f, -3.5f, 3.5f}},
        {"SUBi", UP(0x26, DXYZW, 0, 1, 3), 0, {-0.5f, 0.25f, -5, 2}},
        {"SUBq", UP(0x24, DXYZW, 0, 1, 3), 0, {1.25f, 2, -3.25f, 3.75f}},
        {"MADDq", UP(0x21, DXYZW, 0, 1, 3), 0, {10.375f, 20.5625f, 29.25f, 41}},
        {"MSUBq", UP(0x25, DXYZW, 0, 1, 3), 0, {9.625f, 19.4375f, 30.75f, 39}},
        {"MAXz", UP(0x12, DXYZW, 2, 1, 3), 0, {3, 3, 3, 4}},
        {"MINI", UP(0x2F, DXYZW, 2, 1, 3), 0, {1.5f, 0.5f, -3, -8}},
        {"MULq", UP(0x1C, DXYZW, 0, 1, 3), 0, {0.375f, 0.5625f, -0.75f, 1}},
        {"ADDw", UP(0x03, DXYZW, 2, 1, 3), 0, {-6.5f, -5.75f, -11, -4}},
    };
    unsigned i, c;
    for (i = 0; i < sizeof k / sizeof k[0]; i++) {
        pair_t p[1];
        const uint32_t *got;
        vu_pair d;
        p[0].up = k[i].up;
        p[0].lo = LNOP;
        fresh();
        setv(&V, 1, 1.5f, 2.25f, -3.0f, 4.0f);
        setv(&V, 2, 2.25f, 0.5f, 3.0f, -8.0f);
        V.acc.f[0] = 10; V.acc.f[1] = 20; V.acc.f[2] = 30; V.acc.f[3] = 40;
        V.i = F(2.0f);
        V.q = F(0.25f);
        run_prog(&V, p, 1);
        vu_decode_pair(LNOP, k[i].up, &d);
        got = k[i].to_acc ? V.acc.u : V.vf[3].u;
        for (c = 0; c < 4; c++)
            if (got[c] != F(k[i].r[c])) {
                printf("FAIL %s (%s) lane %u: %g, expected %g\n", k[i].name, vu_upper_name(&d.up), c,
                       (double)AF(got[c]), (double)k[i].r[c]);
                g_fail++;
            }
    }
}

static void t_efu2(void)
{
    const pair_t p[] = {
        {UNOP, EFU(0x71, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DX, 2)},  /* ersadd 1/25 */
        {UNOP, EFU(0x73, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DY, 2)},  /* erleng 1/5 */
        {UNOP, EFU(0x74, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DZ, 2)},  /* eatanxy */
        {UNOP, EFU(0x75, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DW, 2)},  /* eatanxz */
    };
    fresh();
    setv(&V, 1, 3.0f, 4.0f, 0.0f, 5.0f);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vf[2].u[0], 0x3D23D70A);  /* 0.04 chopped */
    CHECKX(V.vf[2].u[1], 0x3E4CCCCC);  /* 0.2 chopped */
    CHECK(fabs(V.vf[2].f[2] - atan(4.0 / 3.0)) < 1e-6);
    CHECKX(V.vf[2].u[3], 0);
}

static void t_vf0_const(void)
{
    const pair_t p[] = {{ADD(DXYZW, 0, 1, 1), MOVE(DXYZW, 0, 1)}, {ADD(DXYZW, 2, 0, 0), LNOP}};
    fresh();
    setv(&V, 1, 5, 6, 7, 8);
    run_prog(&V, p, 2);
    CHECKV(&V, 0, 0.0f, 0.0f, 0.0f, 1.0f);
    CHECKV(&V, 2, 0.0f, 0.0f, 0.0f, 2.0f);
}

static void t_opmula_cross(void)
{
    const pair_t p[] = {{OPMULA(1, 2), LNOP}, {OPMSUB(3, 2, 1), LNOP}};
    fresh();
    setv(&V, 1, 1, 2, 3, 0);
    setv(&V, 2, 4, 5, 6, 0);
    setv(&V, 3, 0, 0, 0, 77);
    run_prog(&V, p, 2);
    CHECKV(&V, 3, -3.0f, 6.0f, -3.0f, 77.0f);
    CHECKX(V.acc.u[0], F(12.0f));
    CHECKX(V.acc.u[1], F(12.0f));
    CHECKX(V.acc.u[2], F(5.0f));
}

static void t_float_edges(void)
{
    const pair_t p[] = {
        {MUL(DX | DY, 3, 1, 2), LNOP},   /* overflow / exact max */
        {MUL(DXYZW, 4, 5, 6), LNOP},     /* inf/nan inputs, denormal, underflow */
        {ADD(DX | DY, 7, 8, 9), LNOP},   /* round toward zero */
        {UNOP, LNOP},
    };
    unsigned c;
    fresh();
    setvu(&V, 1, 0x7F7FFFFF, 0x7F7FFFFF, 0, 0);
    setv(&V, 2, 4.0f, 2.0f, 0, 0);
    setvu(&V, 5, 0x7F800000, 0x7FC00000, 0x00000001, F(ldexpf(1.0f, -100)));
    setvu(&V, 6, F(0.5f), F(0.5f), F(1.0f), F(ldexpf(1.0f, -100)));
    setvu(&V, 8, F(1.0f), F(-1.0f), 0, 0);
    setvu(&V, 9, 0x33C00000, 0xB3C00000, 0, 0); /* +-1.5 * 2^-24 */
    run_prog(&V, p, 4);
    CHECKX(V.vf[3].u[0], 0x7FFFFFFF); /* 2^129: saturates */
    CHECKX(V.vf[3].u[1], 0x7FFFFFFF); /* (2-e)*2^128 is representable */
    CHECKX(V.vf[4].u[0], 0x7F000000); /* 0x7F800000 is 2^128, not inf */
    CHECKX(V.vf[4].u[1], 0x7F400000); /* 0x7FC00000 is 1.5*2^128, not NaN */
    CHECKX(V.vf[4].u[2], 0x00000000); /* denormal reads as zero */
    CHECKX(V.vf[4].u[3], 0x00000000); /* 2^-200 underflows */
    CHECKX(V.vf[7].u[0], 0x3F800000); /* chopped, IEEE RN would give 0x3F800001 */
    CHECKX(V.vf[7].u[1], 0xBF800000);
    /* flag helpers directly */
    {
        unsigned cond;
        CHECKX(vu_f_mul(0x7F7FFFFF, F(4.0f), &cond), 0x7FFFFFFF);
        CHECK(cond == 8);
        CHECKX(vu_f_mul(F(-ldexpf(1, -100)), F(ldexpf(1, -100)), &cond), 0x80000000);
        CHECK(cond == (1 | 2 | 4)); /* Z S U */
        CHECKX(vu_f_add(F(1.0f), F(-1.0f), &cond), 0);
        CHECK(cond == 1);
    }
    (void)c;
}

static void t_ftoi_itof(void)
{
    const pair_t p[] = {
        {FTOI(0, DXYZW, 2, 1), LNOP},
        {FTOI(1, DXYZW, 3, 1), LNOP},
        {FTOI(2, DXYZW, 4, 1), LNOP},
        {FTOI(3, DXYZW, 5, 1), LNOP},
        {ITOF(0, DXYZW, 6, 10), LNOP},
        {ITOF(1, DXYZW, 7, 10), LNOP},
        {ITOF(2, DXYZW, 8, 10), LNOP},
        {ITOF(3, DXYZW, 9, 10), LNOP},
    };
    fresh();
    setv(&V, 1, -2.7f, 1.5f, 3e9f, -3e9f);
    setvu(&V, 10, (uint32_t)-5, 24, 2048, 0x8000);
    run_prog(&V, p, 8);
    CHECKX(V.vf[2].u[0], (uint32_t)-2);
    CHECKX(V.vf[2].u[1], 1);
    CHECKX(V.vf[2].u[2], 0x7FFFFFFF);
    CHECKX(V.vf[2].u[3], 0x80000000);
    CHECKX(V.vf[3].u[1], 24);
    CHECKX(V.vf[3].u[0], (uint32_t)-43); /* -2.7*16 = -43.2 */
    CHECKX(V.vf[4].u[1], 6144);
    CHECKX(V.vf[5].u[1], 49152);
    CHECKX(V.vf[6].u[0], F(-5.0f));
    CHECKX(V.vf[7].u[1], F(1.5f));
    CHECKX(V.vf[8].u[2], F(0.5f));
    CHECKX(V.vf[9].u[3], F(1.0f));
    /* no FMAC flags from conversions */
    CHECKX(V.mac, 0);
}

/* ---------------------------------------------------------------- flags */

static void t_mac_latency(void)
{
    /* SUB gives all-zero -> MAC 0x000F, visible 4 cycles after issue */
    const pair_t p[] = {
        {SUB(DXYZW, 3, 1, 1), LNOP},
        {UNOP, FMAND(4, 2)}, /* distance 1 */
        {UNOP, FMAND(5, 2)}, /* 2 */
        {UNOP, FMAND(6, 2)}, /* 3 */
        {UNOP, FMAND(7, 2)}, /* 4 */
        {UNOP, FSAND(8, 0xFFF)},
        {UNOP, FMEQ(9, 10)},
        {UNOP, FMOR(11, 12)},
        {UNOP, FSSET(0)},
        {UNOP, FSAND(13, 0xFFF)},
        {UNOP, FSEQ(14, 0x001)},
        {UNOP, FSOR(15, 0x800)},
    };
    fresh();
    setv(&V, 1, 1, 2, 3, 4);
    V.vi[2] = 0xFFFF;
    V.vi[10] = 0x000F;
    V.vi[12] = 0x0100;
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vi[4], 0);
    CHECKX(V.vi[5], 0);
    if (g_control) CHECKX(V.vi[6], 0x000F); /* control: claims latency 3 */
    else CHECKX(V.vi[6], 0);
    CHECKX(V.vi[7], 0x000F);
    CHECKX(V.vi[8], VU_ST_Z | VU_ST_ZS);
    CHECKX(V.vi[9], 1);
    CHECKX(V.vi[11], 0x010F);
    CHECKX(V.vi[13], VU_ST_Z);
    CHECKX(V.vi[14], 1);
    CHECKX(V.vi[15], 0x801);
}

static void t_mac_dest_mask(void)
{
    /* x negative, y would be zero but is outside dest: its flags are cleared */
    const pair_t p[] = {{SUB(DX, 3, 1, 2), LNOP}, {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
                        {UNOP, FMAND(4, 5)}};
    fresh();
    setv(&V, 1, 1, 2, 3, 4);
    setv(&V, 2, 2, 2, 3, 4);
    V.vi[5] = 0xFFFF;
    run_prog(&V, p, 5);
    CHECKX(V.vi[4], 0x0080);
}

static void t_flags_overflow_underflow(void)
{
    const pair_t p[] = {{MUL(DX | DW, 3, 1, 2), LNOP}};
    fresh();
    setvu(&V, 1, 0x7F7FFFFF, 0, 0, F(ldexpf(1, -100)));
    setvu(&V, 2, F(4.0f), 0, 0, F(-ldexpf(1, -100)));
    run_prog(&V, p, 1);
    CHECKX(V.mac, 0x8000 | 0x0100 | 0x0010 | 0x0001); /* Ox, Uw, Sw, Zw */
    CHECKX(V.status, VU_ST_Z | VU_ST_S | VU_ST_U | VU_ST_O | VU_ST_ZS | VU_ST_SS | VU_ST_US | VU_ST_OS);
}

static void t_stall_shifts_flags(void)
{
    /* the ADD waits 3 cycles for vf1, so the FMAND right after it already
     * sees the MUL's flags (Zx), and not yet the ADD's (Sx) */
    const pair_t p[] = {
        {MUL(DXYZW, 1, 2, 3), LNOP},
        {ADD(DX, 4, 1, 5), LNOP},
        {UNOP, FMAND(6, 7)},
        {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
        {UNOP, FMAND(8, 7)},
    };
    fresh();
    setv(&V, 2, 0, 1, 1, 1);
    setv(&V, 3, 1, 1, 1, 1);
    setv(&V, 5, -1, 0, 0, 0);
    V.vi[7] = 0xFFFF;
    run_prog(&V, p, 7);
    CHECKX(V.vi[6], 0x0008);
    CHECKX(V.vi[8], 0x0080);
    CHECK(V.stats.stall_cycles == 3);
}

static void t_clip(void)
{
    const pair_t p[] = {
        {CLIP(1, 1), LNOP},
        {CLIP(2, 2), LNOP},
        {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
        {UNOP, FCGET(3)},
        {UNOP, FCAND(0x20)},
        {UNOP, IADD(4, 1, 0)},
        {UNOP, FCEQ(0x260)},
        {UNOP, IADD(5, 1, 0)},
        {UNOP, FCOR(0xFFFD9F)},
        {UNOP, IADD(6, 1, 0)},
        {UNOP, FCAND(0x10)},
        {UNOP, IADD(7, 1, 0)},
        {UNOP, FCSET(0x123456)},
        {UNOP, FCGET(8)},
    };
    fresh();
    setv(&V, 1, 2.0f, -2.0f, 0.5f, 1.0f);
    setv(&V, 2, 0.0f, 0.0f, -5.0f, -1.0f); /* |w| is used */
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vi[3], 0x260);
    CHECKX(V.vi[4], 1);
    CHECKX(V.vi[5], 1);
    CHECKX(V.vi[6], 1);
    CHECKX(V.vi[7], 0);
    CHECKX(V.vi[8], 0x456);
    CHECKX(V.clip, 0x123456);
}

static void t_clip_24bit(void)
{
    /* five CLIPs shift the oldest result out of the 24-bit register */
    const pair_t p[] = {{CLIP(1, 1), LNOP}, {CLIP(2, 2), LNOP}, {CLIP(2, 2), LNOP},
                        {CLIP(2, 2), LNOP}, {CLIP(2, 2), LNOP}};
    fresh();
    setv(&V, 1, 2.0f, 0, 0, 1.0f);
    setv(&V, 2, 0, 0, 0, 1.0f);
    run_prog(&V, p, 5);
    CHECKX(V.clip, 0);
}

/* ---------------------------------------------------------------- FDIV / EFU */

static void t_q_latency(void)
{
    pair_t p[9];
    int k;
    fresh();
    p[0].up = UNOP;
    p[0].lo = DIV(1, 0, 1, 1); /* 8 / 2 */
    for (k = 1; k <= 8; k++) { p[k].up = ADDq(DX, 2 + k, 0); p[k].lo = LNOP; }
    setv(&V, 1, 8, 2, 0, 0);
    V.q = F(1.0f);
    run_prog(&V, p, 9);
    for (k = 1; k <= 8; k++) CHECKX(V.vf[2 + k].u[0], F(k < 7 ? 1.0f : 4.0f));
    CHECK(V.stats.q_early_reads == 6);
}

static void t_waitq_and_div_chain(void)
{
    /* the retail head program's pattern: DIV, DIV (stalls on the first),
     * then Q reads exactly when each result lands */
    const pair_t p[] = {
        {UNOP, DIV(0, 3, 5, 0)},
        {UNOP, DIV(0, 3, 5, 1)},
        {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
        {ADDq(DX, 6, 0), LNOP},
        {ADDq(DY, 6, 0), LNOP},
        {UNOP, DIV(0, 3, 5, 2)},
        {UNOP, WAITQ},
        {ADDq(DZ, 6, 0), LNOP},
    };
    fresh();
    setv(&V, 5, 2.0f, 4.0f, 8.0f, 0);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKV(&V, 6, 0.5f, 0.25f, 0.125f, 0.0f);
}

static void t_div_special(void)
{
    const pair_t p[] = {
        {UNOP, DIV(1, 0, 1, 1)}, {UNOP, WAITQ}, {ADDq(DX, 2, 0), FSAND(3, 0xFFF)},
        {UNOP, DIV(1, 2, 1, 1)}, {UNOP, WAITQ}, {ADDq(DY, 2, 0), FSAND(4, 0x030)},
        {UNOP, DIV(1, 1, 1, 1)}, {UNOP, WAITQ}, {ADDq(DZ, 2, 0), FSAND(5, 0x030)},
        {UNOP, SQRT(1, 3)}, {UNOP, WAITQ}, {ADDq(DW, 2, 0), FSAND(6, 0x030)},
        {UNOP, RSQRT(1, 0, 7, 0)}, {UNOP, WAITQ}, {ADDq(DX, 8, 0), FSAND(9, 0x030)},
        {UNOP, FSAND(10, 0xC00)},
    };
    fresh();
    setv(&V, 1, 1.0f, 0.0f, -1.0f, -4.0f);
    setv(&V, 7, 4.0f, 0, 0, 0);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vf[2].u[0], 0x7FFFFFFF); /* 1/0 */
    CHECKX(V.vi[3] & 0x30, VU_ST_D);
    CHECKX(V.vf[2].u[1], 0xFFFFFFFF); /* -1/0 */
    CHECKX(V.vi[4], VU_ST_D);
    CHECKX(V.vf[2].u[2], 0x7FFFFFFF); /* 0/0 */
    CHECKX(V.vi[5], VU_ST_I);
    CHECKX(V.vf[2].u[3], F(3.0f)); /* vf0.w + sqrt(-4): 1 + 2, I flag */
    CHECKX(V.vi[6], VU_ST_I);
    CHECKX(V.vf[8].u[0], F(0.5f)); /* 1/sqrt(4) */
    CHECKX(V.vi[9], 0);
    CHECKX(V.vi[10], VU_ST_IS | VU_ST_DS);
}

static void t_efu(void)
{
    const pair_t p[] = {
        {UNOP, EFU(0x70, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DX, 2)},             /* esadd 25 */
        {UNOP, EFU(0x72, 1, 0)}, {UNOP, MFP(DY, 2)}, {UNOP, WAITP}, {UNOP, MFP(DZ, 2)}, /* eleng 5 */
        {UNOP, EFU(0x76, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DW, 2)},             /* esum 12 */
        {UNOP, EFU(0x7A, 1, 0)}, {UNOP, WAITP}, {UNOP, MFP(DX, 3)},             /* ercpr 1/3 */
        {UNOP, EFU(0x78, 1, 1)}, {UNOP, WAITP}, {UNOP, MFP(DY, 3)},             /* esqrt 2 (of 4) */
        {UNOP, EFU(0x7D, 4, 0)}, {UNOP, WAITP}, {UNOP, MFP(DZ, 3)},             /* eatan(1) */
        {UNOP, EFU(0x7E, 4, 1)}, {UNOP, WAITP}, {UNOP, MFP(DW, 3)},             /* eexp(-0) */
        {UNOP, EFU(0x79, 1, 1)}, {UNOP, WAITP}, {UNOP, MFP(DX, 5)},             /* ersqrt(4) */
        {UNOP, EFU(0x7C, 4, 1)}, {UNOP, WAITP}, {UNOP, MFP(DY, 5)},             /* esin(0) */
    };
    fresh();
    setv(&V, 1, 3.0f, 4.0f, 0.0f, 5.0f);
    setv(&V, 4, 1.0f, 0.0f, 0, 0);
    V.p = F(-1.0f);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vf[2].u[0], F(25.0f));
    CHECKX(V.vf[2].u[1], F(25.0f)); /* read before ELENG landed: old P */
    CHECKX(V.vf[2].u[2], F(5.0f));
    CHECKX(V.vf[2].u[3], F(12.0f));
    CHECKX(V.vf[3].u[0], 0x3EAAAAAA); /* chopped 1/3 */
    CHECKX(V.vf[3].u[1], F(2.0f));
    CHECKX(V.vf[3].u[2], 0x3F490FDA); /* pi/4 chopped */
    CHECKX(V.vf[3].u[3], F(1.0f));
    CHECKX(V.vf[5].u[0], F(0.5f));
    CHECKX(V.vf[5].u[1], 0);
}

/* ---------------------------------------------------------------- integer / memory */

static void t_integer(void)
{
    const pair_t p[] = {
        {UNOP, IADD(3, 1, 2)},
        {UNOP, ISUB(4, 1, 2)},
        {UNOP, IADDI(5, 1, -16)},
        {UNOP, IADDIU(6, 0, 0x7FFF)},
        {UNOP, ISUBIU(7, 1, 6)},
        {UNOP, IAND(8, 1, 2)},
        {UNOP, IOR(9, 1, 2)},
        {UNOP, IADD(0, 1, 2)},
        {UNOP, IADDIU(10, 6, 0x7FFF)},
        {UNOP, MTIR(11, 1, 1)},
        {UNOP, MFIR(DXYZW, 2, 5)},
    };
    fresh();
    V.vi[1] = 5;
    V.vi[2] = 3;
    setvu(&V, 1, 0, 0x12345678, 0, 0);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vi[3], 8);
    CHECKX(V.vi[4], 2);
    CHECKX(V.vi[5], 0xFFF5);
    CHECKX(V.vi[6], 0x7FFF);
    CHECKX(V.vi[7], 0xFFFF);
    CHECKX(V.vi[8], 1);
    CHECKX(V.vi[9], 7);
    CHECKX(V.vi[0], 0);
    CHECKX(V.vi[10], 0xFFFE);
    CHECKX(V.vi[11], 0x5678);
    CHECKX(V.vf[2].u[0], 0xFFFFFFF5);
    CHECKX(V.vf[2].u[3], 0xFFFFFFF5);
}

static void t_memory(void)
{
    const pair_t p[] = {
        {UNOP, LQ(DX | DY | DW, 1, 1, -2)},  /* qw 10 */
        {UNOP, SQ(DY | DZ, 2, 0, 3)},        /* qw 3 */
        {UNOP, ILW(DY, 2, 0, 20)},
        {UNOP, ILW(DX, 3, 0, 20)},
        {UNOP, ISW(DX | DW, 4, 0, 21)},
        {UNOP, LQ(DXYZW, 7, 5, 1)},          /* (0x3FF + 1) wraps to qw 0 */
        {UNOP, LQI(DXYZW, 8, 6)},            /* qw 10, vi6 -> 11 */
        {UNOP, SQD(DXYZW, 2, 9)},            /* --vi9 = 4 */
        {UNOP, SQI(DXYZW, 2, 9)},            /* qw 4 again, vi9 -> 5 */
        {UNOP, LQD(DXYZW, 10, 6)},           /* --vi6 = 10 */
        {UNOP, ILWR(DZ, 11, 12)},            /* qw 20 z */
        {UNOP, ISWR(DY, 4, 12)},             /* qw 20 y = 0xABCD */
    };
    uint32_t *m = (uint32_t *)V.mem;
    fresh();
    m = (uint32_t *)V.mem;
    m[40] = F(1); m[41] = F(2); m[42] = F(3); m[43] = F(4);
    m[0] = 0x11; m[1] = 0x22; m[2] = 0x33; m[3] = 0x44;
    m[80] = 0x11111; m[81] = 0x2222; m[82] = 0xFFFF8000; m[83] = 0x4444;
    m[84] = 1; m[85] = 2; m[86] = 3; m[87] = 4;
    V.vi[1] = 12; V.vi[4] = 0xABCD; V.vi[5] = 0x3FF; V.vi[6] = 10; V.vi[9] = 5; V.vi[12] = 20;
    setv(&V, 1, 9, 9, 9, 9);
    setv(&V, 2, 5, 6, 7, 8);
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKV(&V, 1, 1, 2, 9, 4);
    CHECKX(m[12], 0); CHECKX(m[13], F(6)); CHECKX(m[14], F(7)); CHECKX(m[15], 0);
    CHECKX(V.vi[2], 0x2222);
    CHECKX(V.vi[3], 0x1111);
    CHECKX(m[84], 0xABCD); CHECKX(m[85], 2); CHECKX(m[86], 3); CHECKX(m[87], 0xABCD);
    CHECKX(V.vf[7].u[0], 0x11);
    CHECKV(&V, 8, 1, 2, 3, 4);
    CHECKX(V.vi[9], 5);
    CHECKX(m[16], F(5)); CHECKX(m[19], F(8));
    CHECKX(V.vi[6], 10);
    CHECKV(&V, 10, 1, 2, 3, 4);
    CHECKX(V.vi[11], 0x8000);
    CHECKX(m[81], 0xABCD);
}

static void t_move_mr32(void)
{
    const pair_t p[] = {{UNOP, MR32(DXYZW, 2, 1)}, {UNOP, MOVE(DX | DZ, 3, 1)}};
    fresh();
    setv(&V, 1, 1, 2, 3, 4);
    setv(&V, 3, 9, 9, 9, 9);
    run_prog(&V, p, 2);
    CHECKV(&V, 2, 2, 3, 4, 1);
    CHECKV(&V, 3, 1, 9, 3, 9);
}

static void t_pair_order(void)
{
    /* the lower op sees the register values from before the paired upper */
    const pair_t p[] = {{ADD(DXYZW, 1, 2, 2), MOVE(DXYZW, 3, 1)}, {UNOP, SQ(DXYZW, 1, 0, 7)},
                        {ADD(DXYZW, 4, 1, 1), SQ(DXYZW, 4, 0, 8)}};
    fresh();
    setv(&V, 1, 7, 7, 7, 7);
    setv(&V, 2, 1, 2, 3, 4);
    setv(&V, 4, 5, 5, 5, 5);
    run_prog(&V, p, 3);
    CHECKV(&V, 3, 7, 7, 7, 7);
    CHECKV(&V, 1, 2, 4, 6, 8);
    CHECKX(((uint32_t *)V.mem)[28], F(2));
    CHECKX(((uint32_t *)V.mem)[32], F(5)); /* old vf4 */
    CHECKV(&V, 4, 4, 8, 12, 16);
}

static void t_loi(void)
{
    /* the upper of an I-bit pair still sees the previous I (the retail VU0
     * sin/cos code depends on this) */
    const pair_t p[] = {
        {UNOP | U_I, F(2.0f)},
        {ADDi(DX, 1, 0) | U_I, F(3.0f)},
        {ADDi(DX, 2, 0), LNOP},
    };
    fresh();
    V.i = F(0.5f);
    run_prog(&V, p, 3);
    CHECKX(V.vf[1].u[0], F(2.0f));
    CHECKX(V.vf[2].u[0], F(3.0f));
    CHECKX(V.i, F(3.0f));
}

static void t_random(void)
{
    const pair_t p[] = {
        {UNOP, RINIT(1, 0)}, {UNOP, RGET(DX, 2)}, {UNOP, RNEXT(DX, 3)},
        {UNOP, RXOR(1, 1)}, {UNOP, RGET(DY, 4)},
    };
    fresh();
    setvu(&V, 1, 0x12345678, 0x00FF00FF, 0, 0);
    run_prog(&V, p, 5);
    CHECKX(V.vf[2].u[0], 0x3FB45678);
    CHECKX(V.vf[3].u[0], 0x3FE8ACF1);
    CHECKX(V.vf[4].u[1], 0x3F97AC0E);
}

/* ---------------------------------------------------------------- control flow */

static void t_branches(void)
{
    /* counted loop with a delay slot; the gap pair keeps clear of the
     * integer-branch hazard */
    const pair_t p[] = {
        /* 0 */ {UNOP, IADDIU(1, 0, 3)},
        /* 1 */ {UNOP, LNOP},
        /* 2 */ {UNOP, IADDI(2, 2, 1)},
        /* 3 */ {UNOP, IADDI(1, 1, -1)},
        /* 4 */ {UNOP, LNOP},
        /* 5 */ {UNOP, IBNE(1, 0, 2 - 6)},
        /* 6 */ {UNOP, IADDI(3, 3, 1)},
        /* 7 */ {UNOP, BAL(15, 12 - 8)},
        /* 8 */ {UNOP, IADDI(4, 4, 1)},
        /* 9 */ {UNOP, IADDI(5, 5, 1)},
        /* 10 */ {UNOP, B(15 - 11)},
        /* 11 */ {UNOP, LNOP},
        /* 12 */ {UNOP, IADDI(6, 6, 7)},
        /* 13 */ {UNOP, JR(15)},
        /* 14 */ {UNOP, LNOP},
        /* 15 */ {UNOP, IADDIU(10, 0, 18)},
        /* 16 */ {UNOP, LNOP},
        /* 17 */ {UNOP, JALR(14, 10)},
        /* 18 */ {UNOP, LNOP},
        /* 19 */ {UNOP, IADDI(7, 7, 1)},
    };
    fresh();
    run_prog(&V, p, (int)(sizeof p / sizeof p[0]));
    CHECKX(V.vi[2], 3);
    CHECKX(V.vi[3], 3);
    CHECKX(V.vi[4], 1);
    CHECKX(V.vi[5], 1);
    CHECKX(V.vi[6], 7);
    CHECKX(V.vi[15], 9);
    CHECKX(V.vi[14], 19);
    CHECKX(V.vi[7], 1);
}

static void t_cond_branches(void)
{
    /* each taken branch skips one marker increment */
    static const struct { uint32_t op; int taken; } k[] = {
        {IBLTZ(1, 2), 1}, {IBGEZ(1, 2), 0}, {IBLEZ(1, 2), 1}, {IBGTZ(1, 2), 0},
        {IBLEZ(0, 2), 1}, {IBGEZ(0, 2), 1}, {IBGTZ(0, 2), 0}, {IBGTZ(2, 2), 1},
        {IBEQ(1, 3, 2), 1}, {IBNE(1, 3, 2), 0}, {IBEQ(1, 2, 2), 0}, {IBNE(1, 2, 2), 1},
    };
    unsigned i;
    for (i = 0; i < sizeof k / sizeof k[0]; i++) {
        pair_t p[4];
        p[0].up = UNOP; p[0].lo = k[i].op;
        p[1].up = UNOP; p[1].lo = LNOP;
        p[2].up = UNOP; p[2].lo = IADDI(9, 9, 1);
        p[3].up = UNOP; p[3].lo = LNOP;
        fresh();
        V.vi[1] = 0xFFFF; V.vi[2] = 1; V.vi[3] = 0xFFFF;
        run_prog(&V, p, 4);
        if (V.vi[9] != (k[i].taken ? 0 : 1)) {
            printf("FAIL cond branch case %u: marker %u\n", i, V.vi[9]);
            g_fail++;
        }
    }
}

static void t_ebit_tpc(void)
{
    const pair_t p[] = {
        {UNOP, LNOP},
        {UNOP | U_E, LNOP},
        {UNOP, IADDI(1, 1, 1)},   /* delay slot of E: runs */
        {UNOP, IADDI(2, 2, 1)},   /* runs only after MSCNT */
        {UNOP | U_E, LNOP},
        {UNOP, LNOP},
    };
    fresh();
    load_prog(&V, p, 6);
    vu_start(&V, 0);
    CHECK(vu_run(&V, 1000) == VU_STOP_EBIT);
    CHECKX(V.vi[1], 1);
    CHECKX(V.vi[2], 0);
    CHECKX(V.tpc, 3 * 8);
    vu_continue(&V);
    CHECK(vu_run(&V, 1000) == VU_STOP_EBIT);
    CHECKX(V.vi[2], 1);
    CHECKX(V.tpc, 6 * 8);
}

static void t_ebit_with_branch(void)
{
    /* the retail head program ends with "nop[e] / b 0x328": the delay slot
     * runs and TPC becomes the branch target */
    const pair_t p[] = {
        {UNOP | U_E, B(5 - 1)},
        {UNOP, IADDI(1, 1, 1)},
        {UNOP, IADDI(2, 2, 1)},
        {UNOP, LNOP}, {UNOP, LNOP},
        {UNOP, LNOP},
    };
    fresh();
    load_prog(&V, p, 6);
    vu_start(&V, 0);
    CHECK(vu_run(&V, 1000) == VU_STOP_EBIT);
    CHECKX(V.vi[1], 1);
    CHECKX(V.vi[2], 0);
    CHECKX(V.tpc, 5 * 8);
}

static void t_int_branch_quirk(void)
{
    const pair_t p[] = {
        /* 0 */ {UNOP, IADDIU(1, 0, 5)},
        /* 1 */ {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
        /* 5 */ {UNOP, IADDI(1, 1, -5)},
        /* 6 */ {UNOP, IBEQ(1, 0, 9 - 7)},
        /* 7 */ {UNOP, LNOP},
        /* 8 */ {UNOP, IADDI(2, 2, 1)},
        /* 9 */ {UNOP, LNOP},
    };
    const pair_t q[] = {
        {UNOP, IADDIU(1, 0, 5)},
        {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP}, {UNOP, LNOP},
        {UNOP, FCAND(0xFFFFFF)},     /* vi1 = 0, flag op: no hazard */
        {UNOP, IBEQ(1, 0, 9 - 7)},
        {UNOP, LNOP},
        {UNOP, IADDI(2, 2, 1)},
        {UNOP, LNOP},
    };
    fresh();
    run_prog(&V, p, 10);
    CHECKX(V.vi[2], 1);                 /* branch read the old vi1 (5) */
    CHECK(V.stats.int_branch_quirks == 1);
    fresh();
    V.int_branch_quirk = 0;
    run_prog(&V, p, 10);
    CHECKX(V.vi[2], 0);
    fresh();
    run_prog(&V, q, 10);
    CHECKX(V.vi[2], 0);
}

/* ---------------------------------------------------------------- XGKICK / TOP */

static uint8_t g_kick[0x4000];
static uint32_t g_kick_bytes, g_kick_addr, g_kicks;

static void kick_sink(void *user, const uint8_t *d, uint32_t n, uint32_t addr)
{
    (void)user;
    memcpy(g_kick, d, n);
    g_kick_bytes = n;
    g_kick_addr = addr;
    g_kicks++;
}

static void put_tag(uint32_t *m, uint32_t qw, uint32_t nloop, int eop, int flg, int nreg)
{
    m[qw * 4 + 0] = nloop | ((uint32_t)eop << 15);
    m[qw * 4 + 1] = ((uint32_t)flg << 26) | ((uint32_t)nreg << 28);
    m[qw * 4 + 2] = 0x5;
    m[qw * 4 + 3] = 0;
}

static void t_xgkick(void)
{
    const pair_t p[] = {{UNOP, IADDIU(1, 0, 0x100)}, {UNOP, LNOP}, {UNOP, XGKICK(1)}};
    uint32_t *m;
    int k;
    fresh();
    m = (uint32_t *)V.mem;
    put_tag(m, 0x100, 2, 0, 0, 1);         /* PACKED 2x1 */
    for (k = 0; k < 8; k++) m[0x101 * 4 + k] = 0xA0 + k;
    put_tag(m, 0x103, 3, 1, 1, 2);         /* REGLIST 3x2 = 6 dwords = 3 qw */
    for (k = 0; k < 12; k++) m[0x104 * 4 + k] = 0xB0 + k;
    V.gif_sink = kick_sink;
    g_kicks = 0;
    run_prog(&V, p, 3);
    CHECK(g_kicks == 1);
    CHECKX(g_kick_bytes, 7 * 16);
    CHECKX(g_kick_addr, 0x1000);
    CHECK(memcmp(g_kick, V.mem + 0x1000, 7 * 16) == 0);
    /* IMAGE, NREG = 0 meaning 16, and a packet that never ends */
    put_tag(m, 0x200, 5, 1, 2, 0);
    CHECKX(vu_gif_packet_bytes(&V, 0x2000), 6 * 16);
    put_tag(m, 0x200, 1, 1, 0, 0);
    CHECKX(vu_gif_packet_bytes(&V, 0x2000), 17 * 16);
    memset(V.mem, 0, sizeof V.mem);
    CHECKX(vu_gif_packet_bytes(&V, 0), 0);
}

static void t_xtop(void)
{
    const pair_t p[] = {{UNOP, XTOP(1)}, {UNOP, XITOP(2)}};
    fresh();
    V.top = 0x123;
    V.itop = 0x45;
    run_prog(&V, p, 2);
    CHECKX(V.vi[1], 0x123);
    CHECKX(V.vi[2], 0x45);
}

static void t_vu0_window(void)
{
    static vu_state v1;
    const pair_t p[] = {
        {UNOP, IADDIU(1, 0, 0x405)}, {UNOP, LNOP},
        {UNOP, LQ(DXYZW, 1, 1, 0)},
        {UNOP, SQ(DXYZW, 1, 1, 1)},     /* -> VU1 vf06 */
        {UNOP, IADDIU(3, 0, 0x423)},
        {UNOP, LNOP},
        {UNOP, ILW(DX, 2, 3, 0)},       /* VU1 vi03 */
        {UNOP, LQ(DXYZW, 2, 0, 0x100)}, /* VU0 data wraps at 4 KB */
    };
    vu_init(&v1, 1);
    fresh();
    vu_init(&V, 0);
    V.vu1 = &v1;
    setv(&v1, 5, 1, 2, 3, 4);
    v1.vi[3] = 0x77;
    ((uint32_t *)V.mem)[0] = 0xCAFE;
    run_prog(&V, p, 8);
    CHECKV(&V, 1, 1, 2, 3, 4);
    CHECKV(&v1, 6, 1, 2, 3, 4);
    CHECKX(V.vi[2], 0x77);
    CHECKX(V.vf[2].u[0], 0xCAFE);
}

static void t_runaway_budget(void)
{
    const pair_t p[] = {{UNOP, B(-1)}, {UNOP, LNOP}};
    fresh();
    load_prog(&V, p, 2);
    vu_start(&V, 0);
    CHECK(vu_run(&V, 500) == VU_STOP_CYCLES);
    CHECK(V.running);
}

/* ---------------------------------------------------------------- main */

typedef struct { const char *name; void (*fn)(void); } test_t;
static const test_t k_tests[] = {
    {"decode_retail", t_decode_retail},
    {"arith", t_arith},
    {"acc_forms", t_acc_forms},
    {"efu2", t_efu2},
    {"vf0_const", t_vf0_const},
    {"opmula_cross", t_opmula_cross},
    {"float_edges", t_float_edges},
    {"ftoi_itof", t_ftoi_itof},
    {"mac_latency", t_mac_latency},
    {"mac_dest_mask", t_mac_dest_mask},
    {"flags_overflow_underflow", t_flags_overflow_underflow},
    {"stall_shifts_flags", t_stall_shifts_flags},
    {"clip", t_clip},
    {"clip_24bit", t_clip_24bit},
    {"q_latency", t_q_latency},
    {"waitq_div_chain", t_waitq_and_div_chain},
    {"div_special", t_div_special},
    {"efu", t_efu},
    {"integer", t_integer},
    {"memory", t_memory},
    {"move_mr32", t_move_mr32},
    {"pair_order", t_pair_order},
    {"loi", t_loi},
    {"random", t_random},
    {"branches", t_branches},
    {"cond_branches", t_cond_branches},
    {"ebit_tpc", t_ebit_tpc},
    {"ebit_with_branch", t_ebit_with_branch},
    {"int_branch_quirk", t_int_branch_quirk},
    {"xgkick", t_xgkick},
    {"xtop", t_xtop},
    {"vu0_window", t_vu0_window},
    {"runaway_budget", t_runaway_budget},
};

int main(int argc, char **argv)
{
    unsigned i;
    int ran = 0;
    const char *want = argc > 1 ? argv[1] : NULL;
    if (want && !strcmp(want, "mac_latency_control")) {
        g_control = 1;
        want = "mac_latency";
    }
    for (i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        int before = g_fail;
        if (want && strcmp(want, k_tests[i].name)) continue;
        k_tests[i].fn();
        printf("%s %s\n", g_fail == before ? "ok  " : "FAIL", k_tests[i].name);
        ran++;
    }
    if (!ran) { printf("no test named %s\n", want); return 2; }
    return g_fail ? 1 : 0;
}
