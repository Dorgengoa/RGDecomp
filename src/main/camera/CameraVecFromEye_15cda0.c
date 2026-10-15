#include "types.h"

extern void VecSub_13be40(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004810A4;

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

void CameraVecFromEye_15cda0(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s32 rv0;
    s32 t1;

    t0 = D_004810A4;
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = D_004810A4->mF20;
        rv0 = t1;
    }
    VecSub_13be40(p0, p1, (rv0 + 0x170));
}
