#include "types.h"
/* insect 0x004F1A60 -- 38 instructions.  A three-arm dispatch on the mode:
 * mode 0 and mode 1 each drive a pair of sub-object calls, and every other
 * mode RECURSES with mode 1.  Both guards branch INTO their arm (`beq` then
 * `beql`) and the compare order is the REVERSE of the arm layout, which is
 * the switch spelling and not an if/else-if chain
 * ([[insect-dispatch-branch-polarity]]).  The `addiu $2,$0,1` hoisted to word
 * 2 is the shared 1 -- the case label and the recursion argument.  $f20 holds
 * the float across the calls. */

typedef struct Obj {
    u8  pad00[0x60];
    s32 m60;                        /* +0x60 */
    u8  pad64[0x70 - 0x64];
    s32 m70;                        /* +0x70 */
} Obj;

extern void insect_InsectBattleCamApplyEye_4f3320(Obj *o, s32 *a);
extern void insect_InsectBattleCamApplyTarget_4f32b0(Obj *o, s32 *a);
extern void insect_InsectBattleCamSetEyeGoal_4f3220(Obj *o, s32 *a);
extern void insect_InsectBattleCamSetTargetGoal_4f30c0(Obj *o, s32 *a, f32 t, s32 c);

void insect_InsectBattleCamRestoreSaved_4f1a60(Obj *o, s32 mode, s32 c, f32 t)
{
    switch (mode) {
    case 0:
        insect_InsectBattleCamApplyEye_4f3320(o, &o->m60);
        insect_InsectBattleCamApplyTarget_4f32b0(o, &o->m70);
        break;
    case 1:
        insect_InsectBattleCamSetEyeGoal_4f3220(o, &o->m60);
        insect_InsectBattleCamSetTargetGoal_4f30c0(o, &o->m70, t, c);
        break;
    default:
        insect_InsectBattleCamRestoreSaved_4f1a60(o, 1, c, t);
        break;
    }
}
