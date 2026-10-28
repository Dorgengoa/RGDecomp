/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vu0native-tests (ctest vu0native, docs/NATIVE-CPU.md):
 *   srt        rg_vu0_srt (VU float rules) bit-exact against the interpreter
 *              running the retail microprogram, on edge and random inputs
 *              (zero-angle branches, denormal angles, large angles);
 *   srt_ieee   the same algorithm in IEEE single (RG_VU0_MODE=native) within
 *              2e-6 of the VU result, and both against S * Rx * Ry * Rz in
 *              double;
 *   local      RG_VU0_LOCAL: every function has its own register file (a
 *              value set in one call reads as reset in the next, in either
 *              file), a frame helper writes its caller's file, a named
 *              context (port/vu0_ctx.h) is shared across files;
 *   ieee       the native float rules (x/0 = +-max, sqrt |x|, ftoi saturation,
 *              round to nearest).
 * --wrong flips one expectation per check (the control must fail).
 * Exit 77 when the retail ELF is missing (srt needs it; the rest still runs
 * first and must pass). */
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "port/vu0.h"

int vnr_setup(void);
int vnr_srt(const rg_vu_u32 s[4], const rg_vu_u32 r[4], const rg_vu_u32 t[4], rg_vu_u32 out[16]);
void rg_vu0_srt_ieee(rg_vf out[4], const rg_vf *s, const rg_vf *r, const rg_vf *t);
/* vu0native_local_a.c / _b.c / vu0native_ieee.c */
void vnl_a_set5(float x);
float vnl_a_get5(void);
void vnl_b_set5(float x);
float vnl_b_get5(void);
float vnl_a_roundtrip(float x);
void vnl_ctx_a_set5(float x);
float vnl_ctx_b_get5(void);
int vni_check(int wrong);

/* the named context of the `local` check (port/vu0_ctx.h) */
rg_vu0_state rg_vu0_ctx_vntest = { { { { 0.0f, 0.0f, 0.0f, 1.0f } } } };

static int g_wrong;
static int g_fail;

#define CHECK(c, ...) do { if (!(c)) { g_fail++; printf("FAIL %s:%d: ", __FILE__, __LINE__); \
    printf(__VA_ARGS__); printf("\n"); } } while (0)

static unsigned g_seed = 0x2468ACE1u;
static unsigned rnd(void)
{
    g_seed = g_seed * 1664525u + 1013904223u;
    return g_seed;
}
static float frand(float lo, float hi)
{
    return lo + (hi - lo) * (float)((rnd() >> 8) & 0xFFFFFF) / 16777216.0f;
}

static void hand(const float s[4], const float a[4], const float t[4], double m[4][4])
{
    double cx = cos(a[0]), sx = sin(a[0]), cy = cos(a[1]), sy = sin(a[1]);
    double cz = cos(a[2]), sz = sin(a[2]);
    double X[3][3] = {{1, 0, 0}, {0, cx, sx}, {0, -sx, cx}};
    double Y[3][3] = {{cy, 0, -sy}, {0, 1, 0}, {sy, 0, cy}};
    double Z[3][3] = {{cz, sz, 0}, {-sz, cz, 0}, {0, 0, 1}};
    double T[3][3], R[3][3];
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            T[i][j] = 0;
            for (k = 0; k < 3; k++)
                T[i][j] += X[i][k] * Y[k][j];
        }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            R[i][j] = 0;
            for (k = 0; k < 3; k++)
                R[i][j] += T[i][k] * Z[k][j];
        }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            m[i][j] = s[i] * R[i][j];
        m[i][3] = 0;
    }
    m[3][0] = t[0];
    m[3][1] = t[1];
    m[3][2] = t[2];
    m[3][3] = 1;
}

static void check_local(void)
{
    vnl_a_set5(3.0f);
    vnl_b_set5(5.0f);
    /* function-local frames: nothing survives the call, in either file */
    CHECK(vnl_a_get5() == (g_wrong ? 3.0f : 0.0f), "file A vf5 = %g", vnl_a_get5());
    CHECK(vnl_b_get5() == 0.0f, "file B vf5 = %g", vnl_b_get5());
    /* a frame helper loads its caller's register file */
    CHECK(vnl_a_roundtrip(2.5f) == 2.5f, "helper roundtrip = %g", vnl_a_roundtrip(2.5f));
    /* named context: written in A's context file, read in B's */
    vnl_ctx_a_set5(7.5f);
    CHECK(vnl_ctx_b_get5() == 7.5f, "shared context = %g", vnl_ctx_b_get5());
}

static int check_srt(void)
{
    int rc = vnr_setup(), n, i, bad = 0, ncases = 0;
    double worst_ieee = 0, worst_hand_vu = 0, worst_hand_ieee = 0;
    if (rc == 77)
        return 77;
    CHECK(rc == 0, "interpreter setup failed");
    if (rc)
        return 0;
    for (n = 0; n < 200000; n++) {
        rg_vf s, r, t, o[4], oi[4];
        rg_vu_u32 ref[16];
        int k;
        for (k = 0; k < 4; k++) {
            s.f[k] = frand(-4.0f, 4.0f);
            t.f[k] = frand(-1000.0f, 1000.0f);
            r.f[k] = frand(-3.5f, 3.5f);
        }
        switch (n % 16) {           /* the program's branches and edge inputs */
        case 0: r.f[0] = r.f[1] = r.f[2] = 0.0f; break;            /* -> 0x378 */
        case 1: r.f[0] = r.f[1] = 0.0f; break;                     /* -> 0x218 */
        case 2: r.f[2] = 0.0f; break;                              /* skip Rz */
        case 3: r.u[0] = 0x00012345u; r.u[1] = 0x80000000u; break; /* denormal / -0 = zero */
        case 4: r.f[k = rnd() % 3] = frand(-100.0f, 100.0f); break; /* large angle */
        case 5: r.f[rnd() % 3] = (rnd() & 1) ? 3.14159265f : -1.57079633f; break;
        case 6: r.u[rnd() % 3] = rnd(); break;                      /* any bits */
        case 7: s.u[rnd() % 3] = 0x00000001u; break;                /* denormal scale */
        default: break;
        }
        ncases++;
        rg_vu0_srt(o, &s, &r, &t);
        if (vnr_srt(s.u, r.u, t.u, ref)) {
            CHECK(0, "interpreter did not end");
            break;
        }
        if (g_wrong && n == 7)
            o[1].u[2] ^= 1;
        if (memcmp(o, ref, 64) != 0) {
            if (bad++ < 5) {
                printf("mismatch case %d: s=%08X %08X %08X r=%08X %08X %08X\n", n,
                       s.u[0], s.u[1], s.u[2], r.u[0], r.u[1], r.u[2]);
                for (i = 0; i < 16; i++)
                    if (o[i / 4].u[i % 4] != ref[i])
                        printf("  [%d][%d] native %08X interp %08X\n", i / 4, i % 4,
                               o[i / 4].u[i % 4], ref[i]);
            }
        }
        /* IEEE form and the hand matrix, on finite well-scaled inputs */
        if (n % 16 >= 8 || n % 16 <= 2) {
            double m[4][4];
            rg_vu0_srt_ieee(oi, &s, &r, &t);
            hand(s.f, r.f, t.f, m);
            for (i = 0; i < 16; i++) {
                double a = o[i / 4].f[i % 4], b = oi[i / 4].f[i % 4], h = m[i / 4][i % 4];
                double sc = (i / 4 == 3) ? 1000.0 : 4.0; /* magnitude of the row */
                double d1 = fabs(a - b) / sc, d2 = fabs(a - h) / sc, d3 = fabs(b - h) / sc;
                if (d1 > worst_ieee) worst_ieee = d1;
                if (d2 > worst_hand_vu) worst_hand_vu = d2;
                if (d3 > worst_hand_ieee) worst_hand_ieee = d3;
            }
        }
    }
    printf("srt: %d cases, %d mismatches vs the interpreter; |vu-ieee| <= %.3g, |vu-hand| <= %.3g, "
           "|ieee-hand| <= %.3g (relative to the row scale)\n",
           ncases, bad, worst_ieee, worst_hand_vu, worst_hand_ieee);
    CHECK(bad == 0, "%d of %d cases differ from the interpreter", bad, ncases);
    CHECK(worst_ieee < 2e-6, "IEEE form off by %g", worst_ieee);
    CHECK(worst_hand_vu < 4e-6 && worst_hand_ieee < 4e-6, "polynomial off the hand matrix");
    return 0;
}

int main(int argc, char **argv)
{
    int i, srt;
    for (i = 1; i < argc; i++)
        if (!strcmp(argv[i], "--wrong"))
            g_wrong = 1;
    check_local();
    g_fail += vni_check(g_wrong);
    srt = check_srt();
    printf("%s (%d failures)\n", g_fail ? "FAIL" : (srt == 77 ? "PASS (srt skipped)" : "PASS"), g_fail);
    if (g_fail)
        return 1;
    return srt == 77 ? 77 : 0;
}
