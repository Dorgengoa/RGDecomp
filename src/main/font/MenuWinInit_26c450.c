#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    u8 pad00C[0x20];
    s32 m2C;
    s32 m30;
    u8 pad034[0xC];
    u128 m40;
    s32 m50;
    s32 m54;
    s32 m58;
    s32 m5C;
    s32 m60;
    s32 m64;
    s32 m68;
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
    s32 m7C;
    s32 m80;
    u8 pad084[0x2C];
    s32 mB0;
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    s32 mC4;
    u8 pad0C8[0x8];
    s32 mD0;
    s32 mD4;
    s32 mD8;
    s32 mDC;
};

void MenuWinInit_26c450(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = -1;
    p0->m08 = -1;
    memset((struct Obj0 *)((u8 *)p0 + 0xC), 0, 0x20);
    p0->m30 = 1;
    p0->m2C = 1;
    p0->m40 = 0;
    p0->m5C = 0x43000000;
    p0->m58 = 0x43000000;
    p0->m54 = 0x43000000;
    p0->m50 = 0x43000000;
    p0->m68 = 0;
    p0->m64 = 0;
    p0->m70 = 0;
    p0->m6C = 0;
    p0->m78 = 0;
    p0->m74 = 0;
    p0->m80 = 0x3F800000;
    p0->m7C = 0x3F800000;
    p0->m60 = 0;
    p0->mB0 = 0;
    p0->mB4 = 0;
    p0->mB8 = 0;
    p0->mBC = 0;
    p0->mC0 = 0;
    p0->mC4 = 0;
    p0->mD0 = 1;
    p0->mD4 = 1;
    p0->mD8 = 0;
    p0->mDC = 0;
}
