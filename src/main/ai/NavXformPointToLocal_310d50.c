#include "types.h"

extern void MatMulPoint_1cb8e0(s32, void *);
extern void VecCopy_1cbe30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x113];
    s8 m113;
};

void NavXformPointToLocal_310d50(struct Obj0 *p0, s32 p1, s32 p2)
{
    s8 t0;

    t0 = p0->m113;
    if (t0 != 0) {
        MatMulPoint_1cb8e0(p1, (struct Obj0 *)((u8 *)p0 + 0x40));
    } else {
        VecCopy_1cbe30(p1, p2);
    }
}
