#include "types.h"

extern s32 ArrayGetChecked_153160(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
};

s32 ArrayGetCheckedIndirect_1527e0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 r0;

    t0 = p0->m00;
    if (t0 != 0) {
        t1 = p0->m08;
        r0 = ArrayGetChecked_153160(t1, p1);
        return r0;
    }
    return 0;
}
