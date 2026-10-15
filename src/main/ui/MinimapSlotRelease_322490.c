#include "types.h"

extern void MinimapRelease_32a1f0(void *);
extern void MinimapSlotSetName_322530(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A0];
    s32 m1A0;
};

void MinimapSlotRelease_322490(struct Obj0 *p0)
{
    MinimapRelease_32a1f0(p0);
    MinimapSlotSetName_322530(p0, 0);
    p0->m1A0 = 0;
}
