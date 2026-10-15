#include "types.h"

extern s32 EvObjCtor_2f9f00(void *);
extern s32 EvObjSwitchInitByName_2f8a90(void *, s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471870[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvObjSwitchCtorWithName_2f8b50(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;
    s32 r1;

    r0 = EvObjCtor_2f9f00(p0);
    p0->mDC = D_00471870;
    r1 = EvObjSwitchInitByName_2f8a90(p0, p1, p2, p3, p4, p5);
    return p0;
}
