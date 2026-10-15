#include "types.h"
/* insect 0x004F3150 -- 200 bytes, 50 instructions, 1 call, 2 conditional
 * branches, br/ins 0.040.  From x_band.py's branch-light band.
 *
 * insect_InsectBattleCamTargetToCell_4f2ff0 is the SAME function against a different record offset
 * (0x90 rather than 0x80) and a different callee; the two sources differ in
 * four tokens.
 *
 * The 16-byte clear at $29+0x30 is written OUT -- a null test on a frame
 * address mwcc cannot fold, then a `sb` do-while whose counter must be
 * UNSIGNED or the bottom test comes out `bgtz` instead of `bnez`.
 *
 * Three `swc1 $f2x` in the prologue are the callee-saved FP registers the
 * three float parameters need across the call; nothing in the source asks.
 *
 * `mul.s $f0, $f1, $f0` has the CONSTANT as the left operand, so the source
 * is `4.0f * (x - 2.0f)` and not `(x - 2.0f) * 4.0f`.
 */

typedef struct Ins {
    u8  pad00[0x80];
    f32 f80;                        /* +0x80 */
    f32 f84;                        /* +0x84 */
    f32 f88;                        /* +0x88 */
} Ins;

extern void insect_InsectBattleCamSetEyeGoal_4f3220(Ins *o, f32 *v, s32 k, f32 w);

void insect_InsectBattleCamEyeToCell_4f3150(Ins *o, s32 k, f32 x, f32 y, f32 z, f32 w)
{
    f32  v[4];
    u8  *p;
    u32  n;

    p = (u8 *)v;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v[0] = 4.0f * (x - 2.0f);
    v[2] = 4.0f * (z - 3.0f);
    v[1] = y;
    insect_InsectBattleCamSetEyeGoal_4f3220(o, v, k, w);
    o->f80 = x;
    o->f84 = y;
    o->f88 = z;
}
