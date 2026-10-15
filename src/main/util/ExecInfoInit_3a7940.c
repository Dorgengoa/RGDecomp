#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

void ExecInfoInit_3a7940(struct Obj0 *p0)
{
    memset(p0, 0, 0x6C);
    p0->m00 = -1;
}
