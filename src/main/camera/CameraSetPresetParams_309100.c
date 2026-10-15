#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
};

void CameraSetPresetParams_309100(struct Obj0 *p0, s32 p1)
{
    if (p1 == 0) {
        p0->m1C = 0x42A00000;
        p0->m20 = 0x429C0000;
        p0->m14 = 0x42B40000;
        p0->m18 = 0;
        p0->m00 = 0x43160000;
        p0->m04 = 0x433E0000;
        p0->m10 = 0;
    } else {
        if (p1 == 1) {
            p0->m1C = 0x41F00000;
            p0->m20 = 0x41200000;
            p0->m14 = 0x42200000;
            p0->m18 = 0xC1F00000;
            p0->m00 = 0x42F00000;
            p0->m04 = 0x43200000;
            p0->m10 = 0;
        }
    }
}
