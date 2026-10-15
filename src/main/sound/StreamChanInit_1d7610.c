#include "types.h"

extern void StreamChanReset_1d75d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x88];
    s32 m88;
};

void StreamChanInit_1d7610(struct Obj0 *p0)
{
    StreamChanReset_1d75d0(p0);
    p0->m88 = 0x3F800000;
}
