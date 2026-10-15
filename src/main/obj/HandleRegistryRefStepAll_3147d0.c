#include "types.h"

extern void HandleRegistryStepAll_314e10(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void HandleRegistryRefStepAll_3147d0(struct Obj0 *p0, s32 p1, f32 fa0)
{
    s32 t0;

    t0 = p0->m00;
    HandleRegistryStepAll_314e10(t0, p1, fa0);
}
