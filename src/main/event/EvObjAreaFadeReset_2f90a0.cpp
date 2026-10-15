#include "types.h"

struct C220 {
    u8 pad000[0xDC];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
};

extern "C" s32 EvObjReset_2f9eb0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE2];
    s16 mE2;
};

extern "C" void EvObjAreaFadeReset_2f90a0(struct Obj0 *p0)
{
    s32 r0;

    r0 = EvObjReset_2f9eb0(p0);
    p0->mE2 = -1;
    ((struct C220 *)p0)->v8();
}
