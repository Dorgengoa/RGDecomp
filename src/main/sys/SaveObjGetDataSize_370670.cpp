#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 SaveObjGetDataSize_370670(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((struct C0 *)p0)->v1();
    r1 = ((struct C0 *)p0)->v0();
    return (r0 - r1);
}
