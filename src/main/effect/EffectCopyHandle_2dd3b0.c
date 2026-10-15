#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    s16 m20;
    u8 pad022[0x2];
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
};

struct Obj1 {
    s16 m00;
    u8 pad002[0x2];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
};

void EffectCopyHandle_2dd3b0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m00 = p1->m20;
    p0->m04 = p1->m24;
    p0->m08 = p1->m28;
    p0->m0C = p1->m2C;
    p0->m10 = p1->m30;
}
