#include "types.h"

extern s32 EventCameraNodeAddStub1C_2539c0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraStubNode1C_263ff0(void)
{
    s32 r;

    r = EventCameraNodeAddStub1C_2539c0(D_00482060);
    return 1;
}
