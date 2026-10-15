#include "types.h"

/* Asks MotionListGetPlayerState_1723a0 about the sub-object at +0x1F0 and returns the second
   word of the 0x30-byte block it fills in.

   The guard is spelled `!= 0` with the value returned inside it, not
   `== 0` with an early `return 0`: retail's `beqzl` carries the zeroing in
   its own delay slot, which is what a one-instruction ELSE body costs. The
   inverted spelling scores the same 86.5% and emits `bnez` plus a wasted
   nop -- the recorded "branch layout follows the SOURCE condition" rule at
   another site. */

extern void MotionListGetPlayerState_1723a0(u8 *obj, s32 which, s32 *out);

s32 ModelObjGetMotionName_1add90(u8 *self)
{
    s32 out[12];

    MotionListGetPlayerState_1723a0(self + 0x1F0, -1, out);
    if (out[1] != 0) {
        return out[1];
    }
    return 0;
}
