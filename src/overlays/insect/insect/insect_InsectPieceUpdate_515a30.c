/* MATCHING (ix48, session 48).  Byte-identical to retail.
 *
 * CLOSED on ONE CONSTRUCT.  The four `_gp`-relative floats are written through
 * a POINTER WALK over `v`, not as four member assignments:
 *
 *     q = (f32 *)&v;
 *     q[0] = D_00481010; q[1] = D_00481014;
 *     q[2] = D_00481018; q[3] = D_0048101C;
 *
 * That gives retail's block instruction-for-instruction, FPR numbering
 * included:  lwc1 a / lwc1 b / lwc1 c / swc1 +0 / swc1 +4 / lwc1 d / swc1 +8 /
 * swc1 +C -- the FOURTH load sits BETWEEN the second and third store, which no
 * member-assignment order can produce.  The `&v` vs `q` argument spelling is
 * inert (both MATCH) and `*q++ =` is byte-identical to `q[i] =`.
 *
 * ⚠ THE MEMBER-ASSIGNMENT AXIS IS COMPLETELY ENUMERATED AND CANNOT REACH IT.
 * ix48b scored ALL 24 orders of `v.a/v.b/v.c/v.d = D_004810XX;` in this coat:
 * `d`-first keeps retail's FPR map (dbca 7, dacb 8, dbac 9, dabc/dcab/dcba 10)
 * and every `a`-first order renumbers every FPR in the block (17-18 bad, 8-11
 * substitutions) -- the park's 7 and the a-first 17 are the two halves of one
 * choice.  Also armed null here: a volatile access-site pin on any subset of
 * the four reads (ix48c, live -- it changes the object -- but never better),
 * the gp block moved before or after the reads, the three `v.a = x;`
 * overwrites moved, a `f32 *pv` local for the argument, `&v.a` as the
 * argument (ix48d).  Sessions 32 and 42 add the read-order sweep, the
 * whole-struct copy, the one-member wrapper and the inlined reads.
 * A probe TU (`build/ix48/vprobe.c`, 11 constructs, ONE compile) found the
 * walk after ~120 scored arms had not; the four globals declared as one ARRAY
 * costs +4 words, the struct copy and the initialiser are both wrong.
 *
 * Previous park header follows.
 * ---------------------------------------------------------------------- */
#include "types.h"
/* insect 0x00515A30 -- 488 bytes, 122 instructions.
 *
 * Three parallel "approach the target" ramps over f78[i]/f84[i]/f90[i], then
 * the same shape once more on the scalar triple fC0/fC4/fC8, then two vector
 * pushes through func_151110 / func_151080.
 *
 * The four `$28`-relative floats at _gp-0x4160.. are ONE struct assignment
 * `v = *(V *)&D_00481010;` -- the same shape insect_InsectPieceAttachSubModel_515210 measured --
 * and the three overwritten slots survive because `v`'s address is taken.
 * The byte-clear at $29+0x30 is written OUT, not memset (insect_InsectBattleDrawDimOverlay_4f52a0).
 */

typedef struct V { f32 a; f32 b; f32 c; f32 d; } V;

typedef struct Obj {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
    u8  pad6E[0x78 - 0x6E];
    f32 f78[3];                     /* +0x78 */
    f32 f84[3];                     /* +0x84 */
    f32 f90[3];                     /* +0x90 */
    u8  pad9C[0xC0 - 0x9C];
    f32 fC0;                        /* +0xC0 */
    f32 fC4;                        /* +0xC4 */
    f32 fC8;                        /* +0xC8 */
    u8  padCC[0xD8 - 0xCC];
    f32 fD8;                        /* +0xD8 */
} Obj;

extern f32 D_00481010;
extern f32 D_00481014;
extern f32 D_00481018;
extern f32 D_0048101C;

extern void insect_InsectPieceHpAnimStepThunk_512d30(Obj *o);
extern void insect_InsectPieceYawOffsetStep_5152d0(Obj *o);
extern f32  insect_InsectPieceGetYawRad_515130(Obj *o);
extern void func_151080(s32 t, f32 *v);
extern void func_151110(s32 t, f32 *v);
extern s32  func_1C4A90(s32 m, s16 i);
extern s32  func_1F5BE0(void);

void insect_InsectPieceUpdate_515a30(Obj *o)
{
    V    v;
    V    w;
    u8  *p;
    u32  n;
    s32  i;
    s32  m;
    s32  t;
    f32  r;
    f32  x;
    f32 *ps;
    f32 *q;
    f32  y;
    f32  z;

    insect_InsectPieceHpAnimStepThunk_512d30(o);
    for (i = 0; i < 3; i++) {
        ps = &o->f90[i];
        if (!*ps) {
            continue;
        }
        o->f78[i] = o->f78[i] + *ps;
        if (*ps > 0.0f) {
            if (o->f78[i] >= o->f84[i]) {
                o->f78[i] = o->f84[i];
                *ps = 0.0f;
            }
        } else {
            if (o->f78[i] <= o->f84[i]) {
                o->f78[i] = o->f84[i];
                *ps = 0.0f;
            }
        }
    }
    if (o->fC8) {
        o->fC0 = o->fC0 + o->fC8;
        if (o->fC8 > 0.0f) {
            if (o->fC0 >= o->fC4) {
                o->fC0 = o->fC4;
                o->fC8 = 0.0f;
            }
        } else {
            if (o->fC0 <= o->fC4) {
                o->fC0 = o->fC4;
                o->fC8 = 0.0f;
            }
        }
    }
    insect_InsectPieceYawOffsetStep_5152d0(o);
    m = func_1F5BE0();
    if (m == 0) {
        return;
    }
    t = func_1C4A90(m, o->f6C);
    if (t == 0) {
        return;
    }
    z = o->f78[2];
    y = o->f78[1] + o->fD8;
    x = o->f78[0];
    q = (f32 *)&v;
    q[0] = D_00481010;
    q[1] = D_00481014;
    q[2] = D_00481018;
    q[3] = D_0048101C;
    v.a = x;
    v.b = y;
    v.c = z;
    func_151110(t, q);
    r = insect_InsectPieceGetYawRad_515130(o);
    p = (u8 *)&w;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    w.b = r;
    w.a = 0.0f;
    w.c = 0.0f;
    func_151080(t, (f32 *)&w);
}
