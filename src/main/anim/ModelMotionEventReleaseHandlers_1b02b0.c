/* ModelMotionEventReleaseHandlers_1b02b0 -- shape-identical to merged GsPktSetFrameMask_13e420 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     GsFrameSetMaskMode_156cc0 -> MotionEventListReleaseHandlers_1b4910
     imm 16 -> 1384
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MotionEventListReleaseHandlers_1b4910(void *, s32);

s32 ModelMotionEventReleaseHandlers_1b02b0(void *p4, s32 a5)
{
    return MotionEventListReleaseHandlers_1b4910((u8 *)p4 + 0x568, a5);
}
