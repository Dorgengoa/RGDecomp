#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00470410[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x68];
    void *m68;
};

struct Obj0 *NodeCtor_18c5b0(struct Obj0 *p0)
{
    p0->m68 = D_00470410;
    return p0;
}
