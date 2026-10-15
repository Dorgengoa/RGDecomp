#include "types.h"

extern s32 AttackObjBaseCopyCtor_3181f0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

extern u8 D_00471BB0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    void *mB0;
    u8 pad0B4[0xEC];
    u128 m1A0;
    u128 m1B0;
    s32 m1C0;
    s32 m1C4;
    s32 m1C8;
    s32 m1CC;
};

struct Obj0 *ProjectileCopyCtor_317f00(struct Obj0 *p0)
{
    s32 r0;

    r0 = AttackObjBaseCopyCtor_3181f0(p0);
    p0->mB0 = D_00471BB0;
    p0->m1C0 = 0;
    p0->m1C4 = 0;
    p0->m1C8 = 0;
    p0->m1CC = 0;
    p0->m1A0 = 0;
    p0->m1B0 = 0;
    return p0;
}
