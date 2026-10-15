#include "types.h"

extern void TargetRefClear_2e71d0(void *);
extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s32 m04;
    f32 m08;
    s32 m0C;
};

void TargetRefSetModelFrame_2e6560(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    TargetRefClear_2e71d0(p0);
    if (p3 != 0) {
        p0->m00 = 5;
        p0->m02 = p1;
        p0->m04 = 0;
        p0->m08 = fa0;
        p0->m0C = p2;
        strcpy((struct Obj0 *)((u8 *)p0 + 0x10), p3);
    }
}
