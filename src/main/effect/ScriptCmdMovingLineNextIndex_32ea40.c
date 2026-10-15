#include "types.h"

extern s32 MovingLineNextIndex_2d8dc0(void);
extern s32 ScriptSlotStoreIntRef_3347f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScriptCmdMovingLineNextIndex_32ea40(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = MovingLineNextIndex_2d8dc0();
    r1 = ScriptSlotStoreIntRef_3347f0(p0, r0);
    return 1;
}
