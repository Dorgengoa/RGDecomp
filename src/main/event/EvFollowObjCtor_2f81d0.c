#include "types.h"

extern s32 EvObjCtor_2f9f00(void *);
extern void TargetRefCtor_2e71f0(void *);
extern s32 EvFollowObjReset_2f8170(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004717D0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvFollowObjCtor_2f81d0(struct Obj0 *p0)
{
    s32 r0;
    s32 r2;

    r0 = EvObjCtor_2f9f00(p0);
    p0->mDC = D_004717D0;
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0xE0));
    r2 = EvFollowObjReset_2f8170(p0);
    return p0;
}
