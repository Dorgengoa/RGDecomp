#include "types.h"

extern void TargetRefClear_2e71d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 pad002[0x2];
    s32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
};

void TargetRefSetPoint_2e6710(struct Obj0 *p0, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    TargetRefClear_2e71d0(p0);
    p0->m00 = 1;
    p0->m04 = 0;
    p0->m08 = fa3;
    p0->m0C = fa0;
    p0->m10 = fa1;
    p0->m14 = fa2;
}
