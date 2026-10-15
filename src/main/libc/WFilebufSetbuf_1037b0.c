#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x66];
    u8 m66;
};

struct Obj0 *WFilebufSetbuf_1037b0(struct Obj0 *p0, s32 p1, s32 p2)
{
    p0->m66 = (p2 != 0);
    return p0;
}
