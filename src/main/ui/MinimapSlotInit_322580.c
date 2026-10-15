#include "types.h"

extern void MinimapSlotSetName_322530(void *, s32);
extern void MinimapInit_32a660(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A0];
    s32 m1A0;
};

void MinimapSlotInit_322580(struct Obj0 *p0)
{
    MinimapSlotSetName_322530(p0, 0);
    p0->m1A0 = 0;
    MinimapInit_32a660(p0);
}
