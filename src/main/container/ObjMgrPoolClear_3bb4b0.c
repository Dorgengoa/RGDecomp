#include "types.h"

extern s32 PoolClear_36ade0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 ObjMgrPoolClear_3bb4b0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 r0;

    t0 = p0->m10;
    rv1 = 1;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        r0 = PoolClear_36ade0(t0);
        rv1 = 1;
    }
    return rv1;
}
