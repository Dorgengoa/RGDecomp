#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x98];
    s32 m98;
    s32 m9C;
    s32 mA0;
};

void DataTableClearHook_4224c0(struct Obj0 *p0)
{
    p0->m98 = 0;
    p0->m9C = 0;
    p0->mA0 = 0;
}
