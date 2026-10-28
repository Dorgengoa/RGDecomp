/* SPDX-License-Identifier: CC0-1.0 */
/* tests/protos: ABI regression cases for the protos stage (docs/PROTOS.md).
 * The fixture game files are staged by run_stage.py at build time and linked
 * against native providers (providers_impl.c, the fixture override); each
 * case calls staged game code and checks the value retail would compute.
 * A control build stages the same files with a deliberate fault and must
 * fail (ctest WILL_FAIL). */
#include <stdio.h>
#include <string.h>

float SoftMul_100000(float a, float b);
long long SoftMulBits_100010(float a, float b);
float SoftMulInt_100020(float a, float b);
void TouchMany_100030(void *v);
float VecLen_1cb3c0(void *v);
void MatFromQuatFull_13c4c0(void *dst, void *q);
void FixCopyUser_13c4e0(void *dst, void *src);
void ModelObjSetMotionRate_1add50(void *m, float vol);
int Host_200000(int x);
int User_200200(int x);
int AliasUser_300100(void);
int IsNeg_500000(double d);
int IconRecId_2a2230(void *c);
int rg_test_vcall_make(void *buf);
int WideCaller_400c00(void *r, unsigned long long *flags);
int WideRetFind_400d00(void *r, unsigned long long mask, unsigned long long *out);
unsigned long long ZextCombine_400e80(const char *a, const char *b);
long long ZextNeg_400f00(const char *a);
float AngleWrapT_401200(float x);
int V0User_401400(int *o, int f);
int V0EarlyUser_4014c0(int *o, int f);
int U128User_401440(int *p);
void LinkUser_401480(int *p);
extern unsigned int D_00480000[5], D_00480020[5];
extern int g_rate_id, g_rate_slot;
extern float g_rate;

void *HandleUser_401940(unsigned char *o, int k);
void GaijiUser_402040(int *out, unsigned int rgba, unsigned int q);
void PushUser_4020a0(float *p);
int NarrowIntUser_4020e0(int *p);
int NarrowPtrUser_402100(int *p);
static int fails;
#define CHECK(name, cond) do { if (cond) printf("ok   %s\n", name); \
    else { printf("FAIL %s\n", name); fails++; } } while (0)

int main(void)
{
    double six = 6.0;
    long long bits6;
    float v[4] = {1.25f, 0, 0, 0}, dst[4] = {0}, q[4] = {7.5f, 0, 0, 0};
    static double obj[32];   /* 256 aligned bytes for the C++ object */

    memcpy(&bits6, &six, 8);
    CHECK("soft-double nested (int views)", SoftMul_100000(1.5f, 4.0f) == 6.0f);
    CHECK("soft-double s64 carriers (ret/arg bitcast)", SoftMulBits_100010(1.5f, 4.0f) == bits6);
    CHECK("soft-double s32 carriers (double-local)", SoftMulInt_100020(1.5f, 4.0f) == 6.0f);
    TouchMany_100030(v);
    CHECK("x87: void-declared float callee leaves no ST0", VecLen_1cb3c0(v) == 2.5f);
    MatFromQuatFull_13c4c0(dst, q);
    CHECK("arity: missing arg passed through", dst[0] == 7.5f);
    {
        static float vd[4] __attribute__((aligned(16))), vs[4] __attribute__((aligned(16))) = {1, 2, 3, 4};
        FixCopyUser_13c4e0(vd, vs);
        CHECK("arity: provider with array-typedef parameters", vd[0] == 1 && vd[3] == 4);
    }
    ModelObjSetMotionRate_1add50(0, 0.25f);
    CHECK("lanes: float slot remapped", g_rate_id == 0 && g_rate_slot == 3 && g_rate == 0.25f);
    CHECK("hosted static callable from another unit", User_200200(5) == 16 && Host_200000(2) == 6);
    CHECK("address alias renamed to the MAIN symbol", AliasUser_300100() == 7);
    CHECK("double-param: s32 pass-through retyped", IsNeg_500000(-2.5) == 1 && IsNeg_500000(3.0) == 0);
    rg_test_vcall_make(obj);
    CHECK("void def ending in a virtual call returns its value", IconRecId_2a2230(obj) == 0x1234);
    {
        /* mask 0x1_00000001 against flags 1: retail compares all 64 bits (no match);
           the 32-bit C would match. WideNarrow adds 1 + 1 either way. */
        unsigned int rec[2] = {1, 1};
        unsigned long long f1 = 1, f2 = 0x100000001ULL;
        CHECK("wide: 64-bit mask compare keeps the high word",
              WideCaller_400c00(rec, &f1) == 2 && WideCaller_400c00(rec, &f2) == 3);
    }
    {
        /* rec[0] = mask 0x1_00000000 (high word only), rec[1] = 2: retail ORs and
           returns all 64 bits, and mask 0 does not contain the high-word mask; the
           32-bit C returns 2 and matches every high-word-only mask. */
        unsigned int rec[4] = {0, 1, 2, 0};
        unsigned long long acc = 0;
        int hit0 = WideRetFind_400d00(rec, 0, &acc);
        int hit1 = WideRetFind_400d00(rec, 0x100000000ULL, &acc);
        CHECK("wide-ret: 64-bit return / accumulator / inlined mask helper",
              hit0 == 0 && hit1 == 1 && acc == 0x100000002ULL);
    }
    {
        /* 32 one bits parse to s32 -1: retail zero-extends it into the low word
           (0x00000000FFFFFFFF); sign extension would set the high word too. The
           sign-extending caller keeps -1. */
        static const char ones[] = "11111111111111111111111111111111";
        CHECK("ret-zext: zero-extended s32 result in a u64",
              ZextCombine_400e80("", ones) == 0xFFFFFFFFULL
              && ZextCombine_400e80("1", "") == 0x100000000ULL
              && ZextNeg_400f00(ones) == -1LL);
    }
    {
        /* 2026-10-18 rules: EE round-toward-zero trick, listing-driven tail value,
           u128 view of an s32 result, extern "C" block linkage (missing argument) */
        int o[3] = { 11, 22, 33 };
        int p[1] = { 0 };
        float w = AngleWrapT_401200(0.006f);
        CHECK("ee-round-floor: AngleWrap of a small angle is the angle",
              w > 0.0059f && w < 0.0061f && AngleWrapT_401200(4.0f) < -2.28f
              && AngleWrapT_401200(4.0f) > -2.29f);
        CHECK("def-v0-return: both branch tail values reach the caller",
              V0User_401400(o, 0) == 111 && V0User_401400(o, 1) == 122
              && V0EarlyUser_4014c0(o, 0) == 22 && V0EarlyUser_4014c0(o, 1) == 44);
        CHECK("u128-view: s32 result through a u128 view", U128User_401440(o) == 33);
        LinkUser_401480(p);
        CHECK("extern \"C\" block linkage: the caller's own argument passed through",
              p[0] == 7);
    }
    {
        /* both slot-2 entries called the way the slot's callers call them:
           (this, h, dt).  Unpadded, VStepA reads h as dt. */
        typedef int (*step_fn)(void *, void *, float);
        float oa[2] = {0, 10.0f}, ob[2] = {0, 10.0f};
        static int h;
        ((step_fn)(unsigned long)D_00480000[2])(oa, &h, 1.5f);
        ((step_fn)(unsigned long)D_00480020[2])(ob, &h, 1.5f);
        CHECK("vslot-lane: float behind the slot's GPR lanes", oa[1] == 8.5f && ob[1] == 7.0f);
    }
    {
        /* rule short-agg (2026-10-25): the handle the short view dropped is passed through */
        static int e0, e1, e2;
        struct { int pad[2]; int n; unsigned short gen; void *e[4]; } tbl = {
            { 0, 0 }, 3, 0x3C3C, { &e0, &e1, &e2, 0 } };
        CHECK("short-agg: a word-size union argument the view dropped",
              HandleUser_401940((unsigned char *)&tbl, 0x3C3C0001) == &e1
              && HandleUser_401940((unsigned char *)&tbl, 0x3C3C0002) == &e2);
    }
    {
        /* 2026-10-25 manual-row close-out rules (abi3) */
        int out[2] = { 0, 0 };
        float pf[2] = { 0, 0 };
        int sum[2] = { 0x100, 0 };      /* low byte 0, EAX 0x100: AL-only return */
        GaijiUser_402040(out, 0x80402010u, 0x3F800000u);
        CHECK("agg-view: an aligned(8) colour struct reaches an s64 parameter as its bytes",
              out[0] == (int)0x80402010u && out[1] == 0x3F800000);
        PushUser_4020a0(pf);
        CHECK("u128-view extra lane: the floats after a dropped u128",
              pf[0] == 2.0f && pf[1] == 3.0f);
        CHECK("type macro + ret-narrow: an int view of a u8 (`#define RT u8`) definition",
              NarrowIntUser_4020e0(sum) == 0);
        CHECK("ret-narrow-view: a C++ pointer view of a u8 definition",
              NarrowPtrUser_402100(sum) == 0);
    }
    printf("%d failure(s)\n", fails);
    return fails != 0;
}
