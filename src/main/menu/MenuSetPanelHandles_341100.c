#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
    s32 m60;
    s32 m64;
    s32 m68;
};

s32 MenuSetPanelHandles_341100(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m5C = p1;
    p0->m60 = p2;
    p0->m64 = p3;
    p0->m68 = p4;
    return 1;
}
