#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

extern u8 D_00470760[];
extern u8 D_004707C0[];
extern u8 D_00470E30[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
    s32 m14;
    u8 pad018[0x8];
    u128 m20;
    u128 m30;
    s32 m40;
    s32 m44;
    u8 pad048[0x8];
    u128 m50;
    u128 m60;
    s32 m70;
};

struct Obj0 *EffAttachCtorRot_19d2f0(struct Obj0 *p0)
{
    p0->m00 = D_00470E30;
    p0->m04 = -1;
    p0->m00 = D_004707C0;
    p0->m14 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m30 = 0;
    p0->m44 = 0;
    p0->m40 = 0;
    p0->m50 = 0;
    p0->m60 = 0;
    p0->m70 = 0;
    p0->m00 = D_00470760;
    return p0;
}
