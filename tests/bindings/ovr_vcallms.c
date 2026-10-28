/* Bindings test for the vcallms lane: MatFromSRTVu0_13bc90 / MatRotateVu0_13bc20
 * run the retail VU0 microprogram (GfxSysInit's VIF0 upload, read from the
 * retail ELF) through rg_vu0_vcallms on the src/ps2/vu interpreter, with the
 * register file shared with the macro-mode model.  Checked:
 *   - bit-exact against the tests/vu vu0_srt procedure (the program run
 *     directly on a second interpreter), on 500 pseudo-random inputs;
 *   - against hand math (S * Rx * Ry * Rz, row vectors, + T) in double;
 *   - the register file is ONE state: macro writes reach the program
 *     (MatRotateVu0 sets vf1/vf3 with COP2 ops, not memory), program results
 *     reach macro mode, registers the program does not touch survive, and
 *     rg_vu0 equals the interpreter's registers afterwards;
 *   - unbound: vcallms returns -1 and changes nothing.
 * Skips (returns -77) without the retail ELF.  Derived from the game's
 * behaviour; like overrides/, not covered by the repository's CC0 dedication. */
#include "types.h"
#include "bt.h"

extern int bth_vcallms_setup(void);
extern void bth_vcallms_unbind(void);
extern int bth_vu0_srt_ref(const float s[4], const float r[4], const float t[4], float m[16]);
extern void bth_vu0_get_vf(int r, float out[4]);
extern u64 bth_vu0_runs(void);

extern void MatFromSRTVu0_13bc90(void *out, void *s, void *r, void *t);
extern void MatRotateVu0_13bc20(void *m, void *rot);

double sin(double);
double cos(double);

typedef struct { f32 v[4]; } __attribute__((aligned(16))) V4;
typedef struct { f32 m[16]; } __attribute__((aligned(16))) M4;

static u32 g_seed = 12345;
static f32 frand(f32 lo, f32 hi)
{
    g_seed = g_seed * 1664525u + 1013904223u;
    return lo + (hi - lo) * (f32)((g_seed >> 8) & 0xFFFFFF) / 16777216.0f;
}

static void euler(const f32 a[3], double R[3][3])
{
    /* Rx(a0) * Ry(a1) * Rz(a2), row-vector form (tests/vu vu0_srt convention 0) */
    double cx = cos(a[0]), sx = sin(a[0]), cy = cos(a[1]), sy = sin(a[1]);
    double cz = cos(a[2]), sz = sin(a[2]);
    double X[3][3] = {{1, 0, 0}, {0, cx, sx}, {0, -sx, cx}};
    double Y[3][3] = {{cy, 0, -sy}, {0, 1, 0}, {sy, 0, cy}};
    double Z[3][3] = {{cz, sz, 0}, {-sz, cz, 0}, {0, 0, 1}};
    double T[3][3];
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
}

static double dabs(double x) { return x < 0 ? -x : x; }

int bt_ovr_vcallms(void)
{
    int f = 0, n, i, j, rc;
    double worst_hand = 0, worst_rot = 0;
    int mismatches = 0;

    rc = bth_vcallms_setup();
    if (rc == 77)
        return -77;
    BT_EQ(f, rc, 0);
    if (rc)
        return f;

    /* 1. MatFromSRTVu0 vs the direct interpreter run (bit-exact) and hand math */
    for (n = 0; n < 500; n++) {
        V4 s, r, t;
        M4 out, ref;
        double R[3][3];
        for (i = 0; i < 3; i++) {
            s.v[i] = n == 0 ? 1.0f : frand(0.1f, 4.0f);
            r.v[i] = n == 0 ? 0.0f : frand(-6.5f, 6.5f);
            t.v[i] = frand(-100.0f, 100.0f);
        }
        s.v[3] = frand(-2, 2);
        r.v[3] = frand(-2, 2);
        t.v[3] = frand(-2, 2);
        MatFromSRTVu0_13bc90(&out, &s, &r, &t);
        BT_EQ(f, bth_vu0_srt_ref(s.v, r.v, t.v, ref.m), 0);
        if (__builtin_memcmp(&out, &ref, sizeof out) != 0)
            mismatches++;
        euler(r.v, R);
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++) {
                double e = dabs(out.m[i * 4 + j] - s.v[i] * R[i][j]) / (s.v[i] > 1 ? s.v[i] : 1);
                if (e > worst_hand)
                    worst_hand = e;
            }
        for (j = 0; j < 3; j++)
            if (out.m[12 + j] != t.v[j])
                mismatches += 1000;
        if (out.m[15] != 1.0f || out.m[3] != 0.0f || out.m[7] != 0.0f || out.m[11] != 0.0f)
            mismatches += 1000000;
    }
    BT_EQ(f, mismatches, 0);
    printf("vcallms: MatFromSRTVu0 500 inputs, worst |m - S*Rx*Ry*Rz| = %.2e\n", worst_hand);
    BT_NEAR(f, worst_hand, 0, BT_WRONG(0) ? 1e-30 : 1e-5); /* VU sin polynomial + chop rounding */

    /* 2. shared state: rg_vu0 == interpreter registers after the call */
    {
        float v[4];
        int same = 1;
        for (i = 1; i < 32; i++) {
            bth_vu0_get_vf(i, v);
            if (__builtin_memcmp(v, &rg_vu0.vf[i], 16) != 0)
                same = 0;
        }
        BT_EQ(f, same, 1);
    }

    /* 3. MatRotateVu0: m = m * R(rot); vf1/vf3 come from macro ops, vf30 survives */
    for (n = 0; n < 200; n++) {
        M4 m, m0;
        V4 rot, keep;
        double R[3][3];
        for (i = 0; i < 16; i++)
            m.m[i] = frand(-10, 10);
        for (i = 0; i < 3; i++)
            rot.v[i] = frand(-6.5f, 6.5f);
        rot.v[3] = 0;
        /* poison vf1/vf3: the macro vaddw/vmulx must overwrite them before vcallms,
           or the scale (7) / translation (9) would show in the hand-math check */
        for (i = 0; i < 4; i++) {
            rg_vu0.vf[1].f[i] = 7.0f;
            rg_vu0.vf[3].f[i] = 9.0f;
            keep.v[i] = frand(-1, 1);
        }
        rg_vu0_lqc2(30, &keep);
        m0 = m;
        MatRotateVu0_13bc20(&m, &rot);
        euler(rot.v, R);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 3; j++) {
                double e = 0;
                int k;
                for (k = 0; k < 3; k++)
                    e += (double)m0.m[i * 4 + k] * R[k][j];
                e = dabs(m.m[i * 4 + j] - e) / 30.0;
                if (e > worst_rot)
                    worst_rot = e;
            }
        if (m.m[15] != m0.m[15]) /* w of the translation row: w * vf7.w (1) */
            mismatches++;
        if (__builtin_memcmp(&rg_vu0.vf[30], &keep, 16) != 0)
            mismatches += 1000;
    }
    BT_EQ(f, mismatches, 0);
    printf("vcallms: MatRotateVu0 200 inputs, worst |m*R - hand| / 30 = %.2e\n", worst_rot);
    BT_NEAR(f, worst_rot, 0, 1e-5);

    /* 4. unbound: -1, registers unchanged */
    {
        u64 runs = bth_vu0_runs();
        rg_vf before = rg_vu0.vf[4];
        bth_vcallms_unbind();
        rg_vu0.vf[2].f[0] = 1.0f;
        BT_EQ(f, rg_vu0_vcallms(0), -1);
        BT_EQ(f, __builtin_memcmp(&before, &rg_vu0.vf[4], 16), 0);
        BT_EQ(f, bth_vu0_runs(), runs);
        BT_EQ(f, bth_vcallms_setup(), 0);
        BT_EQ(f, rg_vu0_vcallms(0), 0);
        BT_EQ(f, bth_vu0_runs(), runs + 1);
    }
    return f;
}
