#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_0047E9AC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x400];
    s32 m400;
};

void EventIconHide_278be0(void)
{
    D_0047E9AC->m400 = -1;
}
