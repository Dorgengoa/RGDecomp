#include "types.h"

extern s32 EvObjCtor_2f9f00(void *);
extern s32 EvObjLiftReset_336500(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471D70[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xDC];
    void *mDC;
};

struct Obj0 *EvObjLiftCtor_336560(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = EvObjCtor_2f9f00(p0);
    p0->mDC = D_00471D70;
    r1 = EvObjLiftReset_336500(p0);
    return p0;
}
