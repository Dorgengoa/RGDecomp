#include "types.h"

extern s32 memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
};

struct Obj0 *ModelObjExParamBlockCtorMaybe_1ef490(struct Obj0 *p0)
{
    s32 r0;

    r0 = memset(p0, 0, 0x2C);
    p0->m00 = -1;
    p0->m0C = -1;
    p0->m10 = -1;
    p0->m08 = 1;
    p0->m14 = 1;
    p0->m18 = 0x3F800000;
    p0->m1C = 0;
    p0->m20 = -1;
    p0->m24 = 0;
    p0->m28 = 0;
    return p0;
}
