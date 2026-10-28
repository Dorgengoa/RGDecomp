/* VU0 model (include/port/vu0.h), the vu0inline.h replacement, and the
 * vu0asm ingest stage end to end (tests/xlat/ files are translated by
 * tools/portxform.py at build time).  libvu0.h macros: test_libvu0.c.
 * Known vectors only; exit 0 = pass. */
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "vec.h"          /* game/include/vec.h after the int128 stage */
#include "vu0inline.h"    /* resolves to the PORT copy (include/ first) */

int g_vu0_fails;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); g_vu0_fails++; } } while (0)
#define CHECKV(v, X, Y, Z, W) CHECK((v)[0] == (X) && (v)[1] == (Y) && (v)[2] == (Z) && (v)[3] == (W))

extern int test_libvu0(void);
extern void xlat_push_apart(Vec4 *p0, Vec4 *p1, f32 a, f32 b);
extern void xlat_lerp_gnu(u128 *d, u128 *b, f32 t);

static void setvf(int n, float x, float y, float z, float w)
{
    float v[4] __attribute__((aligned(16))) = { x, y, z, w };
    rg_vu0_lqc2(n, v);
}
static unsigned bits(int vf, int lane) { return rg_vu0.vf[vf].u[lane]; }
static void setbits(int vf, int lane, unsigned b) { rg_vu0.vf[vf].u[lane] = b; }

static void test_float_model(void)
{
    /* round toward zero: 1 + 0.75ulp -> 1.0 (IEEE nearest would give 1+ulp) */
    setvf(1, 1.0f, 0, 0, 0);
    setbits(2, 0, 0x33C00000u);                  /* 1.5 * 2^-24 = 0.75 ulp(1) */
    rg_vu0_fmac(RG_VADD, RG_X, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0x3F800000u);
    /* ...and negative results truncate toward zero too */
    setvf(1, -1.0f, 0, 0, 0);
    setbits(2, 0, 0xB3C00000u);
    rg_vu0_fmac(RG_VADD, RG_X, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0xBF800000u);
    /* product truncates: (1+2^-23)^2 = 1 + 2^-22 + 2^-46 -> 1 + 2^-22 */
    setbits(1, 0, 0x3F800001u);
    rg_vu0_fmac(RG_VMUL, RG_X, 3, 1, 1, RG_BC_NONE);
    CHECK(bits(3, 0) == 0x3F800002u);
    /* overflow clamps to +-max (0x7FFFFFFF), never Inf */
    setbits(1, 0, 0x7F7FFFFFu); setbits(1, 1, 0xFF7FFFFFu);
    setvf(2, 4.0f, 4.0f, 0, 0);
    rg_vu0_fmac(RG_VMUL, RG_XY, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0x7FFFFFFFu && bits(3, 1) == 0xFFFFFFFFu);
    /* exponent 255 is a number: "Inf" bits * 0.5 = 2^127 */
    setbits(1, 0, 0x7F800000u);
    setvf(2, 0.5f, 0, 0, 0);
    rg_vu0_fmac(RG_VMUL, RG_X, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0x7F000000u);
    /* denormal inputs read as zero; tiny results flush to signed zero */
    setbits(1, 0, 0x00000001u);
    setvf(2, 0, 0, 0, 0);
    rg_vu0_fmac(RG_VADD, RG_X, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0);
    setbits(1, 0, 0x00800000u); setbits(1, 1, 0x80800000u);   /* +-2^-126 */
    setvf(2, 0.5f, 0.5f, 0, 0);
    rg_vu0_fmac(RG_VMUL, RG_XY, 3, 1, 2, RG_BC_NONE);
    CHECK(bits(3, 0) == 0 && bits(3, 1) == 0x80000000u);
    /* madd/msub: ACC +- product, product rounded first */
    setvf(1, 2, 3, 4, 5); setvf(2, 10, 10, 10, 10);
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 2, RG_BC_NONE);       /* ACC = 20,30,40,50 */
    rg_vu0_fmac(RG_VMSUB, RG_XYZW, 3, 1, 1, RG_BC_NONE);       /* - 4,9,16,25 */
    CHECKV(rg_vu0.vf[3].f, 16, 21, 24, 25);
    /* masks: lanes outside the field keep their value */
    setvf(4, 9, 9, 9, 9);
    rg_vu0_fmac(RG_VADD, RG_XZ, 4, 1, 2, RG_BC_W);              /* + vf2w */
    CHECKV(rg_vu0.vf[4].f, 12, 9, 14, 9);
    /* Q / I sources */
    rg_vu0.q = rg_f2u(0.5f); rg_vu0.i = rg_f2u(3.0f);
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 5, 1, RG_FT_Q, RG_BC_NONE);
    CHECKV(rg_vu0.vf[5].f, 1, 1.5f, 2, 2.5f);
    rg_vu0_fmac(RG_VADD, RG_XYZW, 5, 1, RG_FT_I, RG_BC_NONE);
    CHECKV(rg_vu0.vf[5].f, 5, 6, 7, 8);
    /* max / mini */
    setvf(1, -1, 5, 3, 0); setvf(2, 2, 2, 2, 2);
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 3, 1, 2, RG_BC_X);
    CHECKV(rg_vu0.vf[3].f, 2, 5, 3, 2);
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 3, 1, 2, RG_BC_X);
    CHECKV(rg_vu0.vf[3].f, -1, 2, 2, 0);
    /* vf0 is read-only (0,0,0,1) */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 0, 1, 2, RG_BC_NONE);
    setvf(0, 7, 7, 7, 7);
    CHECKV(rg_vu0.vf[0].f, 0, 0, 0, 1);
    /* div / sqrt / rsqrt incl. x/0 = +-max and sqrt(|x|) */
    setvf(1, 1, -1, 0, 9); setvf(2, 0, 4, -4, 16);
    rg_vu0_div(1, RG_BC_X, 2, RG_BC_X);  CHECK(rg_vu0.q == 0x7FFFFFFFu);
    rg_vu0_div(1, RG_BC_Y, 2, RG_BC_X);  CHECK(rg_vu0.q == 0xFFFFFFFFu);
    rg_vu0_div(1, RG_BC_W, 2, RG_BC_Y);  CHECK(rg_u2f(rg_vu0.q) == 2.25f);
    rg_vu0_sqrt(2, RG_BC_Z);             CHECK(rg_u2f(rg_vu0.q) == 2.0f);
    rg_vu0_rsqrt(1, RG_BC_W, 2, RG_BC_W); CHECK(rg_u2f(rg_vu0.q) == 2.25f);
    /* ftoi / itof */
    setvf(1, 1.5f, -2.75f, 3e9f, -0.5f);
    rg_vu0_ftoi(4, RG_XY, 3, 1);
    CHECK(rg_vu0.vf[3].i[0] == 24 && rg_vu0.vf[3].i[1] == -44);
    rg_vu0_ftoi(0, RG_ZW, 3, 1);
    CHECK(rg_vu0.vf[3].i[2] == 0x7FFFFFFF && rg_vu0.vf[3].i[3] == 0);
    rg_vu0.vf[6].i[0] = 4096; rg_vu0.vf[6].i[1] = -32768; rg_vu0.vf[6].i[2] = 3; rg_vu0.vf[6].i[3] = 0;
    rg_vu0_itof(12, RG_X, 7, 6);  CHECK(rg_vu0.vf[7].f[0] == 1.0f);
    rg_vu0_itof(15, RG_Y, 7, 6);  CHECK(rg_vu0.vf[7].f[1] == -1.0f);
    rg_vu0_itof(0, RG_Z, 7, 6);   CHECK(rg_vu0.vf[7].f[2] == 3.0f);
    /* abs / move / mr32 */
    setvf(1, -1, 2, -3, 4);
    setvf(3, 0, 0, 0, 7);
    rg_vu0_abs(RG_XYZ, 3, 1);   CHECKV(rg_vu0.vf[3].f, 1, 2, 3, 7);
    rg_vu0_move(RG_W, 3, 1);    CHECK(rg_vu0.vf[3].f[3] == 4);
    rg_vu0_mr32(RG_XYZW, 3, 1); CHECKV(rg_vu0.vf[3].f, 2, -3, 4, -1);
    /* outer product: ACC = a.yzx*b.zxy, then a x b */
    setvf(1, 1, 2, 3, 0); setvf(2, 4, 5, 6, 0);
    rg_vu0_opmula(1, 2);
    rg_vu0_opmsub(3, 2, 1);
    CHECK(rg_vu0.vf[3].f[0] == -3 && rg_vu0.vf[3].f[1] == 6 && rg_vu0.vf[3].f[2] == -3);
    /* clip: history shifts by 6 */
    rg_vu0.clip = 0;
    setvf(1, 2, -2, 0.5f, 1); setvf(2, 0, 0, 0, -1);           /* |w| = 1 */
    rg_vu0_clip(1, 2);
    CHECK(rg_vu0.clip == 0x09);                                /* +x, -y */
    rg_vu0_clip(1, 2);
    CHECK(rg_vu0.clip == 0x249);
    rg_vu0_cfc2(RG_GPR_a1, 18);
    CHECK(rg_vu0.gpr[5][0] == 0x249);
    /* GPR transfers: mfc1 sign-extends, qmtc2 moves 128 bits */
    rg_vu0.gpr[8][2] = 0x11111111u; rg_vu0.gpr[8][3] = 0x22222222u;
    rg_vu0_mfc1(RG_GPR_t0, -2.0f);
    CHECK(rg_vu0.gpr[8][0] == 0xC0000000u && rg_vu0.gpr[8][1] == 0xFFFFFFFFu);
    rg_vu0_qmtc2(RG_GPR_t0, 9);
    CHECK(rg_vu0.vf[9].f[0] == -2.0f && bits(9, 2) == 0x11111111u && bits(9, 3) == 0x22222222u);
    rg_vu0_qmfc2(RG_GPR_a2, 9);
    CHECK(rg_vu0_mtc1(RG_GPR_a2) == -2.0f);
    rg_vu0_mfc1(0, 5.0f);
    CHECK(rg_vu0_gpr_r32(0) == 0);
}

static void test_vu0inline(void)
{
    Vec4 d, s;
    Mtx4 m, o;
    f32 *dv = &d.x;
    int i;

    d.x = 1; d.y = 2; d.z = 3; d.w = 4; s.x = 5; s.y = 6; s.z = 7; s.w = 8;
    Vu0CopyVectorXYZ(&d, &s);
    CHECKV(dv, 5, 6, 7, 4);

    Vu0UnitVector(&d);
    CHECKV(dv, 0, 0, 0, 1);

    s.w = 9;
    Vu0CopyVectorW1(&d, &s);
    CHECKV(dv, 5, 6, 7, 1);

    s.x = 1; s.y = 2; s.z = 3; s.w = 100;
    CHECK(Vu0SquareLength(&s) == 14.0f);
    CHECK(rg_vu0.gpr[5][0] == rg_f2u(14.0f));      /* the $a1 clobber */

    {
        Vec4 p1 = { 10, 20, 30, 40 }, p2 = { 0, 0, 0, 0 };
        Vu0InterVector(&d, &p1, &p2, 0.25f);
        CHECKV(dv, 2.5f, 5, 7.5f, 10);
        p1.x = p1.y = p1.z = p1.w = 1; p2.x = 3; p2.y = 5; p2.z = 7; p2.w = 9;
        Vu0InterVector(&d, &p1, &p2, 0.5f);        /* p2 + (p1 - p2) t */
        CHECKV(dv, 2, 3, 4, 5);
    }

    for (i = 0; i < 4; i++) {
        m.r[i].x = 1 + i; m.r[i].y = 10 + i; m.r[i].z = 100 + i; m.r[i].w = 1000 + i;
    }
    s.x = 2; s.y = 4; s.z = 8; s.w = 0;
    Vu0ScaleMatrix(&o, &s, &m);
    CHECKV(&o.r[0].x, 2, 20, 200, 2000);
    CHECKV(&o.r[1].x, 8, 44, 404, 4004);
    CHECKV(&o.r[2].x, 24, 96, 816, 8016);
    CHECKV(&o.r[3].x, 4, 13, 103, 1003);
    Vu0InvScaleMatrix(&m, &s, &o);                 /* undo it */
    CHECKV(&m.r[0].x, 1, 10, 100, 1000);
    CHECKV(&m.r[1].x, 2, 11, 101, 1001);
    CHECKV(&m.r[2].x, 3, 12, 102, 1002);
    CHECKV(&m.r[3].x, 4, 13, 103, 1003);
    CHECK(rg_u2f(rg_vu0.q) == 0.125f);
}

static void test_xlat(void)
{
    /* mwcc block form (DynClothSolveSpring_16a480): push p0/p1 apart to a */
    Vec4 p0 = { 3, 4, 0, 1 }, p1 = { 0, 0, 0, 1 };
    u128 q1, q2;
    f32 *f1 = (f32 *)&q1, *f2 = (f32 *)&q2;
    xlat_push_apart(&p0, &p1, 10.0f, 0.5f);
    CHECKV(&p0.x, 4.5f, 6, 0, 1);
    CHECKV(&p1.x, -1.5f, -2, 0, 1);
    CHECKV(rg_vu0.vf[31].f, 1, 1, 1, 1);           /* side effect kept */

    /* GNU form with raw newlines in the template (AnimKeyBlendMaterial lerp) */
    f1[0] = 1; f1[1] = 2; f1[2] = 3; f1[3] = 4;
    f2[0] = 5; f2[1] = 10; f2[2] = -3; f2[3] = 4;
    xlat_lerp_gnu(&q1, &q2, 0.25f);
    CHECKV(f1, 2, 4, 1.5f, 4);
}

int main(void)
{
    test_float_model();
    test_vu0inline();
    test_xlat();
    g_vu0_fails += !test_libvu0();
    printf("test_vu0: %s (%d failures)\n", g_vu0_fails ? "FAIL" : "PASS", g_vu0_fails);
    return g_vu0_fails != 0;
}
