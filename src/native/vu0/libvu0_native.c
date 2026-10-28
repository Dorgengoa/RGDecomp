/* SPDX-License-Identifier: CC0-1.0 */
/* libvu0 as plain C (docs/NATIVE-CPU.md section 9, PLAN.md D9): the sceVu0*
 * functions the game calls (444 call sites, Sony's names kept: the game calls
 * them unsuffixed), on float lanes.  No VU register file, no COP2 model.
 *
 * Each routine is the retail routine's arithmetic (src/sce/vu0/libvu0.c, which
 * transcribes the COP2 code instruction by instruction onto the VU0 model) in
 * the same operation order with the same lane rounding: the float helpers of
 * port/vu0.h (rg_vu_addf / subf / mulf / divf / sqrtf: IEEE single under
 * RG_VU0_MODE=native with the VU clamp rules where the game can see them, VU
 * rounding under `local`).  So the results are bit-identical to libvu0.c in the
 * same mode (ctest native_vu0.libvu0 compares them on random and edge inputs),
 * including the IEEE signed-zero effects of the VU code's `0 + x` moves.  What
 * libvu0.c leaves behind in its function-local register file is unobservable
 * (vu0frame: no other function sees it), so nothing else is kept.
 *
 * Aliasing as retail: every source row/vector is read before the destination
 * row is written (sceVu0MulMatrix(m, m, m), sceVu0RotMatrix(m, m, r), ...). */
#include "port/vu0.h"

#include <string.h>

#ifdef RG_VU0N_TEST   /* the comparison test links this next to libvu0.c */
#define VU0N(n) rg_vu0n_##n
#else
#define VU0N(n) sceVu0##n
#endif

typedef float vec4[4] __attribute__((aligned(16)));
typedef float mat4[4][4] __attribute__((aligned(16)));
typedef rg_vu_u32 u32;

#define ADD rg_vu_addf
#define SUB rg_vu_subf
#define MUL rg_vu_mulf

static inline u32 bits(float f) { return rg_f2u(f); }
static inline float flt(u32 u) { return rg_u2f(u); }

static inline void load(rg_vf *v, const float *p) { memcpy(v, p, 16); }
static inline void store(float *p, const rg_vf *v) { memcpy(p, v, 16); }

#define ONE 0x3F800000u

/* ---- vectors ------------------------------------------------------------ */

void VU0N(AddVector)(vec4 v0, vec4 v1, vec4 v2)
{
    rg_vf a, b, d;
    int k;
    load(&a, v1);
    load(&b, v2);
    for (k = 0; k < 4; k++)
        d.u[k] = ADD(a.u[k], b.u[k]);
    store(v0, &d);
}

void VU0N(SubVector)(vec4 v0, vec4 v1, vec4 v2)
{
    rg_vf a, b, d;
    int k;
    load(&a, v1);
    load(&b, v2);
    for (k = 0; k < 4; k++)
        d.u[k] = SUB(a.u[k], b.u[k]);
    store(v0, &d);
}

void VU0N(ScaleVector)(vec4 v0, vec4 v1, float t)
{
    rg_vf a, d;
    u32 s = bits(t);
    int k;
    load(&a, v1);
    for (k = 0; k < 4; k++)
        d.u[k] = MUL(a.u[k], s);
    store(v0, &d);
}

/* xyz scaled, w = the source's */
void VU0N(ScaleVectorXYZ)(vec4 v0, vec4 v1, float t)
{
    rg_vf a;
    u32 s = bits(t);
    int k;
    load(&a, v1);
    for (k = 0; k < 3; k++)
        a.u[k] = MUL(a.u[k], s);
    store(v0, &a);
}

/* v0 = v1 * (1 / t): reciprocal first, then the products (two roundings) */
void VU0N(DivVector)(vec4 v0, vec4 v1, float t)
{
    rg_vf a;
    u32 q = rg_vu_divf(ONE, bits(t));
    int k;
    load(&a, v1);
    for (k = 0; k < 4; k++)
        a.u[k] = MUL(a.u[k], q);
    store(v0, &a);
}

/* v0 = v1 * t + v2 * (1 - t), each product rounded, then the sum */
void VU0N(InterVector)(vec4 v0, vec4 v1, vec4 v2, float t)
{
    rg_vf a, b, d;
    u32 s = bits(t);
    u32 one = ADD(0, ONE);
    u32 u = SUB(one, s);
    int k;
    load(&a, v1);
    load(&b, v2);
    for (k = 0; k < 4; k++)
        d.u[k] = ADD(MUL(a.u[k], s), MUL(b.u[k], u));
    store(v0, &d);
}

/* The game declares it void and int; it returns nothing ($v0 untouched).
 * Returning dst keeps both kinds of caller defined. */
void *VU0N(CopyVector)(vec4 v0, vec4 v1)
{
    memmove(v0, v1, 16);
    return v0;
}

/* (x*x' + y*y') + z*z', each step rounded */
float VU0N(InnerProduct)(vec4 v0, vec4 v1)
{
    rg_vf a, b;
    u32 x, y, z;
    load(&a, v0);
    load(&b, v1);
    x = MUL(a.u[0], b.u[0]);
    y = MUL(a.u[1], b.u[1]);
    z = MUL(a.u[2], b.u[2]);
    return flt(ADD(ADD(x, y), z));
}

/* v0 = v1 x v2, w = 0 */
void VU0N(OuterProduct)(vec4 v0, vec4 v1, vec4 v2)
{
    rg_vf a, b, d;
    load(&a, v1);
    load(&b, v2);
    d.u[0] = SUB(MUL(a.u[1], b.u[2]), MUL(b.u[1], a.u[2]));
    d.u[1] = SUB(MUL(a.u[2], b.u[0]), MUL(b.u[2], a.u[0]));
    d.u[2] = SUB(MUL(a.u[0], b.u[1]), MUL(b.u[0], a.u[1]));
    d.u[3] = 0;
    store(v0, &d);
}

/* ---- matrices ----------------------------------------------------------- */

void VU0N(CopyMatrix)(mat4 m0, mat4 m1)
{
    memmove(m0, m1, 64);
}

/* out = c0 * v.x + c1 * v.y + c2 * v.z + c3 * v.w (accumulated in that order) */
static inline void xform(rg_vf *out, const rg_vf c[4], const rg_vf *v)
{
    int k;
    for (k = 0; k < 4; k++) {
        u32 acc = MUL(c[0].u[k], v->u[0]);
        acc = ADD(acc, MUL(c[1].u[k], v->u[1]));
        acc = ADD(acc, MUL(c[2].u[k], v->u[2]));
        out->u[k] = ADD(acc, MUL(c[3].u[k], v->u[3]));
    }
}

/* m0 = m1 * m2 (column-vector convention: row i of the result is m1 applied
 * to row i of m2) */
void VU0N(MulMatrix)(mat4 m0, mat4 m1, mat4 m2)
{
    rg_vf c[4], v, d;
    int i;
    for (i = 0; i < 4; i++)
        load(&c[i], m1[i]);
    for (i = 0; i < 4; i++) {
        load(&v, m2[i]);
        xform(&d, c, &v);
        store(m0[i], &d);
    }
}

void VU0N(TransposeMatrix)(mat4 m0, mat4 m1)
{
    float t[4][4];
    int r, c;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++)
            t[c][r] = m1[r][c];
    memcpy(m0, t, 64);
}

/* Inverse of a rotation+translation matrix: the 3x3 part transposed (w lanes
 * 0), row 3 = -(R^T * t) with w kept from m1[3][3]. */
void VU0N(InversMatrix)(mat4 m0, mat4 m1)
{
    rg_vf t, z, r0, r1, r2, d;
    int k;
    load(&t, m1[3]);
    z = t;
    for (k = 0; k < 3; k++)
        z.u[k] = SUB(t.u[k], t.u[k]);
    r0.f[0] = m1[0][0]; r0.f[1] = m1[1][0]; r0.f[2] = m1[2][0]; r0.u[3] = z.u[0];
    r1.f[0] = m1[0][1]; r1.f[1] = m1[1][1]; r1.f[2] = m1[2][1]; r1.u[3] = z.u[1];
    r2.f[0] = m1[0][2]; r2.f[1] = m1[1][2]; r2.f[2] = m1[2][2]; r2.u[3] = z.u[2];
    d = z;
    for (k = 0; k < 3; k++) {
        u32 acc = MUL(r0.u[k], t.u[0]);
        acc = ADD(acc, MUL(r1.u[k], t.u[1]));
        acc = ADD(acc, MUL(r2.u[k], t.u[2]));
        d.u[k] = SUB(z.u[k], acc);
    }
    store(m0[0], &r0);
    store(m0[1], &r1);
    store(m0[2], &r2);
    store(m0[3], &d);
}

/* ---- rotations ---------------------------------------------------------- */

/* Sony's sin polynomial constants (S5432), read from retail 0x00445F60. */
static const u32 ecossin_k[4] = {0x362E9C14u, 0xB94FB21Fu, 0x3C08873Eu, 0xBE2AAAA4u};

/* _sceVu0ecossin on a (|a| <= pi), neg = the cos sign flag:
 * *s = sin(a) (the odd polynomial), *c = +-sqrt(1 - s*s).  For a = pi/2 -+ r
 * this is (s, c) = (cos r, sin r). */
static void ecossin(u32 a, int neg, u32 *c, u32 *s)
{
    u32 a2 = MUL(a, a);
    u32 k[4], x, q, cc;
    int i;
    x = ADD(0, a);
    for (i = 0; i < 4; i++)
        k[i] = MUL(MUL(ecossin_k[i], a), a2);        /* k * a * a^2 */
    for (i = 0; i < 3; i++)
        k[i] = MUL(k[i], a2);                        /* k.xyz * a^4 */
    x = ADD(x, k[3]);
    for (i = 0; i < 2; i++)
        k[i] = MUL(k[i], a2);                        /* k.xy * a^6 */
    x = ADD(x, k[2]);
    k[0] = MUL(k[0], a2);                            /* k.x * a^8 */
    x = ADD(x, k[1]);
    x = ADD(x, k[0]);
    *s = ADD(0, x);
    q = rg_vu_sqrtf(SUB(ONE, MUL(*s, *s)));
    cc = ADD(0, q);
    *c = neg ? SUB(0, cc) : ADD(0, cc);
}

/* angle prologue of RotMatrixX/Y/Z: a = pi/2 -+ r (EE FPU, IEEE single) */
static void rot_angle(float r, u32 *c, u32 *s)
{
    const float half_pi = rg_u2f(0x3FC90FDBu);
    int neg = r < 0.0f;
    float a = neg ? half_pi + r : half_pi - r;
    ecossin(bits(a), neg, c, s);
}

static void rot_apply(mat4 m0, mat4 m1, const rg_vf col[4])
{
    rg_vf v, d;
    int i;
    for (i = 0; i < 4; i++) {
        load(&v, m1[i]);
        xform(&d, col, &v);
        store(m0[i], &d);
    }
}

/* R built in four columns from (c, s) the way the retail code builds them:
 * every non-trivial lane is `0 + x` / `0 - x` (so -0 inputs come out +0). */
void VU0N(RotMatrixZ)(mat4 m0, mat4 m1, float rz)
{
    rg_vf col[4];
    u32 c, s;
    rot_angle(rz, &c, &s);
    memset(col, 0, sizeof col);
    col[3].u[3] = ONE;
    col[2].u[2] = ONE;
    col[0].u[1] = ADD(0, c);
    col[0].u[0] = ADD(0, s);
    col[1].u[0] = SUB(0, c);
    col[1].u[1] = ADD(0, s);
    rot_apply(m0, m1, col);
}

void VU0N(RotMatrixX)(mat4 m0, mat4 m1, float rx)
{
    rg_vf col[4];
    u32 c, s;
    rot_angle(rx, &c, &s);
    memset(col, 0, sizeof col);
    col[0].u[0] = ADD(0, ONE);
    col[3].u[3] = ADD(0, ONE);
    col[1].u[2] = ADD(0, c);
    col[1].u[1] = ADD(0, s);
    col[2].u[1] = SUB(0, c);
    col[2].u[2] = ADD(0, s);
    rot_apply(m0, m1, col);
}

void VU0N(RotMatrixY)(mat4 m0, mat4 m1, float ry)
{
    rg_vf col[4];
    u32 c, s;
    rot_angle(ry, &c, &s);
    memset(col, 0, sizeof col);
    col[1].u[1] = ADD(0, ONE);
    col[3].u[3] = ADD(0, ONE);
    col[0].u[2] = SUB(0, c);
    col[0].u[0] = ADD(0, s);
    col[2].u[0] = ADD(0, c);
    col[2].u[2] = ADD(0, s);
    rot_apply(m0, m1, col);
}

/* m0 = RotX(rot.x) * RotY(rot.y) * RotZ(rot.z) * m1 */
void VU0N(RotMatrix)(mat4 m0, mat4 m1, vec4 rot)
{
    VU0N(RotMatrixZ)(m0, m1, rot[2]);
    VU0N(RotMatrixY)(m0, m0, rot[1]);
    VU0N(RotMatrixX)(m0, m0, rot[0]);
}
