#include "types.h"

extern s32 EvObjCtor_2f9f00(void *);
extern s32 EvPointObjInitWithPoint_2f9740(void *, s32, s32, f32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471960[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvPointObjCtorWithPoint_2f97f0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    s32 r0;
    s32 r1;

    r0 = EvObjCtor_2f9f00(p0);
    p0->mDC = D_00471960;
    r1 = EvPointObjInitWithPoint_2f9740(p0, p1, p2, fa0, fa1, fa2, fa3);
    return p0;
}
