#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    u8 pad024[0xC];
    s32 m30;
    s16 m34;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

s32 CharaDataNodeGetData_1eeb00(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    if (p1 != 0) {
        p1->m00 = p0->m30;
        p2->m00 = p0->m34;
    }
    return p0->m20;
}
