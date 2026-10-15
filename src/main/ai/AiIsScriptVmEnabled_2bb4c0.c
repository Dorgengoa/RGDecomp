#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB8];
    s32 mB8;
};

s32 AiIsScriptVmEnabled_2bb4c0(struct Obj0 *p0, s32 p1)
{
    s32 rv0;
    s32 t0;
    s32 t1;

    rv0 = (t1 & 1);
    if (p1 == 1) {
        t0 = p0->mB8;
        rv0 = (t0 & 4);
    } else {
        t1 = p0->mB8;
        rv0 = (t1 & 1);
    }
    return rv0;
}
