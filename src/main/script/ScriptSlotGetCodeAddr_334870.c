#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 ScriptSlotGetCodeAddr_334870(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m00;
    if (t0 == 2) {
        t1 = p0->m04;
        return t1;
    }
    return 0;
}
