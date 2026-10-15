#include "types.h"

extern void VecDistance_13d3d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

f32 CameraDistToEye_13fd00(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->mF20;
    if (t0 != 0) {
        VecDistance_13d3d0((t0 + 0x170));
        return;
    }
    return 0.0f;
}
