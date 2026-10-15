#include "types.h"

extern s32 EvObjLiftPlayClose_335a90(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10A];
    s16 m10A;
};

s32 EvObjLiftSnapClosed_335b50(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv1;

    r0 = EvObjLiftPlayClose_335a90(p0, p1);
    rv1 = 1;
    if (r0 == 0) {
        rv1 = 0;
    } else {
        p0->m10A = 0x7FFF;
        rv1 = 1;
    }
    return rv1;
}
