/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamTargetToCell_4f2ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F2FF0 -- 200 bytes, 50 instructions, 1 call, 2 conditional
 * branches, br/ins 0.040.  From x_band.py's branch-light band.
 *
 * insect_InsectBattleCamEyeToCell_4f3150 is the SAME function against a different record offset
 * (0x80 rather than 0x90) and a different callee; the two sources differ in
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
    u8  pad00[0x90];
    f32 f90;                        /* +0x90 */
    f32 f94;                        /* +0x94 */
    f32 f98;                        /* +0x98 */
} Ins;

/*rgp*/

void insect_InsectBattleCamTargetToCell_4f2ff0(Ins *o, s32 k, f32 x, f32 y, f32 z, f32 w)
{
    f32  v[4] __attribute__((aligned(16)));
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
    insect_InsectBattleCamSetTargetGoal_4f30c0(o, v, k, w);
    o->f90 = x;
    o->f94 = y;
    o->f98 = z;
}
