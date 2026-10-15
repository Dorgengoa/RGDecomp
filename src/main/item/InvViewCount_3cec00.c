#include "types.h"

extern s32 InvCountInCategory_3c7ba0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
    s16 m0A;
};

s32 InvViewCount_3cec00(struct Obj0 *p0)
{
    s32 t0;
    s16 t1;
    s16 t2;
    s32 r0;

    t0 = p0->m04;
    if (t0 != 0) {
        t1 = p0->m08;
        t2 = p0->m0A;
        r0 = InvCountInCategory_3c7ba0(t0, t1, t2, 0);
        return r0;
    }
    return 0;
}
