#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    u8 pad014[0x8];
    s16 m1C;
    s16 m1E;
    s16 m20;
    s16 m22;
    u8 pad024[0x60];
    s32 m84;
    s32 m88;
    s32 m8C;
};

void DoorCursorClear_305630(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m22 = 0;
    p0->m1E = 0;
    p0->m84 = 0;
    p0->m88 = 0;
    p0->m8C = 0x3F800000;
    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 2) + 0x14) = 0;
        l0 = (l0 + 1);
    } while (l0 < 2);
    p0->m1C = 0;
    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x24) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x54) = 0;
        l1 = (l1 + 1);
    } while (l1 < 0xC);
}
