#include "types.h"

extern f32 TaggedGetFloat_26a280(s32);
extern s32 EventCameraNodeAddOrbitSetYaw_253dc0(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;

s32 EvCmdCameraSetOrbitYaw_264830(s32 p0)
{
    f32 r0;
    s32 t0;
    s32 r1;

    r0 = TaggedGetFloat_26a280(p0);
    t0 = D_00482060;
    r1 = EventCameraNodeAddOrbitSetYaw_253dc0(t0, r0);
    return 1;
}
