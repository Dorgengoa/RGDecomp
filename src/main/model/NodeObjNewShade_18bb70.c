#include "types.h"

extern s32 MemStackNew_14e230(s32, s32);
extern s32 ZeroQwordPair_18bbb0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x110];
    s32 m110;
};

s32 NodeObjNewShade_18bb70(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = MemStackNew_14e230(0x20, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = ZeroQwordPair_18bbb0(r0);
        p0->m110 = r1;
        rv2 = r1;
    } else {
        p0->m110 = r0;
        rv2 = r0;
    }
    return rv2;
}
