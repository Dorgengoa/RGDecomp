#include "types.h"

extern void ListNodeInit_1efa20(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
    s16 m0A;
    s32 m0C;
    s32 m10;
    u8 pad014[0x8];
    s16 m1C;
    u8 m1E;
    u8 pad01F[0x1];
    s32 m20;
    u8 pad024[0x6];
    s16 m2A;
    s32 m2C;
    s32 m30;
    s16 m34;
    u8 pad036[0x2];
    s32 m38;
};

void CharaDataNodeInit_1ef940(struct Obj0 *p0)
{
    s32 l0;

    p0->m08 = -1;
    p0->m0A = -1;
    p0->m0C = -1;
    p0->m10 = -1;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m20 = 0;
    p0->m1E = 0;
    p0->m2A = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    l0 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l0 << 1) + 0x14) = -1;
        l0 = (l0 + 1);
    } while (l0 < 4);
    ListNodeInit_1efa20(p0, l0);
}
