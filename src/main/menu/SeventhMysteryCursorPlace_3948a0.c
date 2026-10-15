#include "types.h"

extern void UiSetSpritePos_28fd10(void *, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E9550[];

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    u8 pad004[0x2];
    s16 m06;
    u8 pad008[0xA];
    s16 m12;
};

s32 SeventhMysteryCursorPlace_3948a0(struct Obj0 *p0)
{
    s32 l0;
    s16 t0;
    s16 t1;
    s16 t2;
    s16 t3;

    l0 = 0;
    do {
        t0 = p0->m00;
        t1 = p0->m12;
        t2 = p0->m06;
        t3 = p0->m02;
        UiSetSpritePos_28fd10(D_004E9550, 5, ((t0 + 0x3C) - (((l0 * 0x12) + l0) << 1)), ((t3 + 1) + (t1 * t2)), l0);
        l0 = (l0 + 1);
    } while (l0 < 2);
    return 1;
}
