#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    u128 m00;
    u128 m10;
    s32 m20;
    s32 m24;
    s32 m28;
    u8 pad02C[0x14];
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    s32 m50;
    s32 m54;
    s32 m58;
    s32 m5C;
    s32 m60;
    s32 m64;
};

void OutlineParamsInit_16b8b0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m40 = 0x42A00000;
    p0->m44 = 0x42700000;
    p0->m48 = 0;
    p0->m4C = 0x43000000;
    p0->m50 = 1;
    p0->m54 = 1;
    p0->m58 = -1;
    p0->m5C = 0;
    p0->m60 = 0;
    p0->m64 = 1;
}
