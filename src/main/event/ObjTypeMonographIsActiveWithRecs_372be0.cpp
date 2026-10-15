#include "types.h"

struct C220 {
    u8 pad000[0xDC];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
};

extern "C" s32 ObjTypeMonographIsActiveWithRecs_372be0(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    s32 rv1;
    s32 t1;

    r0 = ((struct C220 *)p0)->v3();
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->mE0;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        t1 = p0->mE4;
        rv1 = (t1 != 0);
    }
    return rv1;
}
