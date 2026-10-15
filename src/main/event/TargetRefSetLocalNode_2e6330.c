#include "types.h"

extern void TargetRefSetMapNode_2e6370(void *, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

void TargetRefSetLocalNode_2e6330(struct Obj0 *p0, s32 p1, f32 fa0)
{
    TargetRefSetMapNode_2e6370(p0, -1, p1, fa0);
    p0->m00 = 0xA;
}
