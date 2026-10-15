#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 UiEntryListGetCurrentData_28ec60(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m0C;
    if (t0 != 0) {
        return (t0 + 4);
    }
    return 0;
}
