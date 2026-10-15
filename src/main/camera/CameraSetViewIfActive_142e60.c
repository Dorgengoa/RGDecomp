#include "types.h"

extern void CameraSetView_156200(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

void CameraSetViewIfActive_142e60(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;

    t0 = p0->mF20;
    if (t0 != 0) {
        CameraSetView_156200(t0, p1, p2);
    }
}
