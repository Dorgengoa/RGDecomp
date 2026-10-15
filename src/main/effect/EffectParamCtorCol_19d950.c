#include "types.h"

extern s32 VecSetOnes4_13e170(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

extern u8 D_004708B0[];
extern u8 D_00470A10[];
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
};

struct Obj0 *EffectParamCtorCol_19d950(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = D_00470E30;
    p0->m04 = -1;
    p0->m00 = D_00470A10;
    p0->m14 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m30 = 0;
    p0->m00 = D_004708B0;
    r0 = VecSetOnes4_13e170((struct Obj0 *)((u8 *)p0 + 0x20));
    return p0;
}
