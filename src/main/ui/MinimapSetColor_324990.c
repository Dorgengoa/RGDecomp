#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x116];
    u8 m116;
    u8 m117;
    u8 m118;
    u8 m119;
};

void MinimapSetColor_324990(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m116 = p1;
    p0->m117 = p2;
    p0->m118 = p3;
    p0->m119 = p4;
}
