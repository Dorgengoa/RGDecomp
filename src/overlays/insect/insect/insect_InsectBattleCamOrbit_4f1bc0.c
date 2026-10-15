#include "types.h"
/* insect 0x004F1BC0 -- 1,044 bytes, 264 instructions, 19 calls, 22 conditional
 * branches.  Five f32 parameters in $f12..$f16 and NINE callee-saved FPRs.
 *
 * mwcc evaluates the operands of the `q[k] +- a*f(..) + b*g(..)` sums RIGHT to
 * LEFT -- both accumulator chains call the SECOND-appearing helper FIRST -- so
 * the source order is the natural one.
 *
 * `s` and `t` are the two named products that live ACROSS a call: retail puts
 * each in a CALLEE-SAVED FPR ($f21, $f20), which is what a named local does
 * and what a bare `pd * f(ang) * g(x)` cannot reach (that spelling would call
 * g first).
 *
 * `c.lt.s x,K / bc1f <assign>` is the `>=` clamp (there is no c.ge.s) and
 * `c.le.s x,K / bc1tl` is the `<=` clamp -- read the two polarities off the
 * compare mnemonic, not off the branch.
 *
 * The two 4-float gp copies are TWO V2 half-copies each; the V4 cast is the
 * measured 5-bad arm (ix22 round 1).
 */

typedef struct V2 { f32 x, y; } V2;

typedef struct Obj {
    f32 f00[4];                         /* +0x00 */
    f32 f10[4];                         /* +0x10 */
    u8  pad20[0x30 - 0x20];
    f32 f30;                            /* +0x30 */
    f32 f34;                            /* +0x34 */
    f32 f38;                            /* +0x38 */
    f32 f3C;                            /* +0x3C */
    u8  pad40[0x5D98 - 0x40];
    f32 f5D98;                          /* +0x5D98 */
    u8  pad5D9C[0x5EF8 - 0x5D9C];
    s32 f5EF8;                          /* +0x5EF8 */
} Obj;

extern f32 D_00480FE0;
extern f32 D_00480FE8;
extern f32 D_00480FF0;
extern f32 D_00480FF8;
extern f32 D_0047D838;                  /* _gp - 0x7938 */
extern f32 D_0047D8B8;                  /* _gp - 0x78B8 */
extern f32 D_0047D8BC;                  /* _gp - 0x78B4 */

extern f32  func_1291A8(f32 a, f32 b);
extern f32  func_128D30(f32 a);
extern f32  func_128FD0(f32 a);
extern f32  func_1CB490(f32 *v);
extern f32  func_1CB4C0(f32 *v);
extern void func_1CBD00(f32 *d, f32 *a, f32 *b);
extern void func_1CBD80(f32 *a, f32 *b, f32 *c);
extern f32  func_1CBF30(f32 a);

extern s32  insect_InsectBattleCamTargetSettled_4f1980(Obj *o);
extern s32  insect_InsectBattleCamEyeSettled_4f19f0(Obj *o);
extern void insect_InsectBattleCamApplyTarget_4f32b0(Obj *o, f32 *v);
extern void insect_InsectBattleCamApplyEye_4f3320(Obj *o, f32 *v);

s32 insect_InsectBattleCamOrbit_4f1bc0(Obj *o, f32 px, f32 py, f32 pz, f32 pw, f32 pd)
{
    f32 r[4];
    f32 q[4];
    f32 p[4];
    f32 prev;
    f32 ang;
    f32 d;
    f32 rad;
    f32 t;
    s32 i;

    if (insect_InsectBattleCamEyeSettled_4f19f0(o) == 0 || insect_InsectBattleCamTargetSettled_4f1980(o) == 0) {
        return 0;
    }
    prev = o->f5D98;
    *(V2 *)&q[0] = *(V2 *)&D_00480FE0;
    *(V2 *)&q[2] = *(V2 *)&D_00480FE8;
    *(V2 *)&p[0] = *(V2 *)&D_00480FF0;
    *(V2 *)&p[2] = *(V2 *)&D_00480FF8;
    switch (o->f5EF8) {
    case 0xA:
    case 0xD:
        for (i = 0; i < 4; i++) {
            p[i] = o->f00[i];
        }
        break;
    default:
        for (i = 0; i < 4; i++) {
            q[i] = o->f10[i];
            p[i] = o->f00[i];
        }
        break;
    }
    func_1CBD00(r, p, q);
    d = func_1CB4C0(r);
    ang = func_1291A8(r[1], func_1CB490(r));
    o->f30 = q[0] + px * func_128D30(o->f5D98) + py * func_128FD0(o->f5D98);
    o->f34 = q[1];
    o->f38 = q[2] - px * func_128FD0(o->f5D98) + py * func_128D30(o->f5D98);
    o->f3C = 1.0f;
    o->f5D98 = func_1CBF30(o->f5D98 + pz);
    ang = ang + pw;
    rad = d + pd;
    rad = (rad < 38.0f) ? rad : 38.0f;
    rad = (rad > 26.0f) ? rad : 26.0f;
    ang = (ang < D_0047D838) ? ang : D_0047D838;
    switch (o->f5EF8) {
    case 0xA:
        ang = (ang > D_0047D8BC) ? ang : D_0047D8BC;
        break;
    case 0xD:
        ang = (ang > D_0047D8B8) ? ang : D_0047D8B8;
        break;
    default:
        ang = (ang > D_0047D8B8) ? ang : D_0047D8B8;
        break;
    }
    d = rad * func_128D30(ang);
    r[0] = d * func_128FD0(o->f5D98);
    r[1] = rad * func_128FD0(ang);
    t = rad * func_128D30(ang);
    r[2] = t * func_128D30(o->f5D98);
    r[3] = 0.0f;
    func_1CBD80(p, q, r);
    insect_InsectBattleCamApplyEye_4f3320(o, p);
    insect_InsectBattleCamApplyTarget_4f32b0(o, q);
    switch (o->f5EF8) {
    case 0xA:
    case 0xD:
        for (i = 0; i < 4; i++) {
            o->f10[i] = q[i];
            o->f00[i] = p[i];
        }
        break;
    default:
        for (i = 0; i < 4; i++) {
            o->f10[i] = q[i];
            o->f00[i] = p[i];
        }
        break;
    }
    if (prev > 0.0f && o->f5D98 < 0.0f) {
        return 1;
    }
    if (prev < 0.0f && o->f5D98 > 0.0f) {
        return 2;
    }
    return 0;
}
