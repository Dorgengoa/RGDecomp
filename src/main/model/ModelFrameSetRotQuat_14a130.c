#include "types.h"

extern void MatFromQuat_13c440(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x29];
    u8 m29;
};

void ModelFrameSetRotQuat_14a130(struct Obj0 *p0)
{
    MatFromQuat_13c440((struct Obj0 *)((u8 *)p0 + 0x60));
    p0->m29 = 1;
}
