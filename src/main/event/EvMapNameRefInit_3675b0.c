#include "types.h"

extern void EvMapNameRefReset_3675f0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void EvMapNameRefInit_3675b0(struct Obj0 *p0, s32 p1)
{
    EvMapNameRefReset_3675f0(p0);
    p0->m00 = p1;
}
