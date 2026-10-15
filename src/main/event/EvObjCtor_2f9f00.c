#include "types.h"

extern s32 EventRecCtor_2e5860(void *);
extern void XformCtor_2e79c0(void *);
extern void TargetRefCtor_2e71f0(void *);
extern s32 EvObjReset_2f9eb0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004719B0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvObjCtor_2f9f00(struct Obj0 *p0)
{
    s32 r0;
    s32 r4;

    r0 = EventRecCtor_2e5860(p0);
    p0->mDC = D_004719B0;
    XformCtor_2e79c0((struct Obj0 *)((u8 *)p0 + 0x10));
    XformCtor_2e79c0((struct Obj0 *)((u8 *)p0 + 0x58));
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0xA0));
    r4 = EvObjReset_2f9eb0(p0);
    return p0;
}
