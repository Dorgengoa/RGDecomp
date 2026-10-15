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
};

void MeshBuildParamInitMaybe_15c9b0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0x3F800000;
    p0->m10 = 0x43000000;
    p0->m14 = 0x43000000;
    p0->m18 = 0x43000000;
    p0->m1C = 0x43000000;
}
