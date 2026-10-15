#include "types.h"

extern void StreamChanSetRestoreResumeReq_1d7080(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x80];
    s16 m80;
};

void StreamChanRestoreResumePoint_1d6ad0(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m80;
    if (t0 >= 0) {
        StreamChanSetRestoreResumeReq_1d7080(p0, 1);
    }
}
