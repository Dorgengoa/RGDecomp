#include "types.h"

extern void AiMoveRunToTarget_2be160(s32, void *, s32, s32, f32);
extern void CharaRemoveFlags_212480(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void AiMoveWalkToTarget_2be2e0(s32 p0, struct Obj0 *p1, s32 p2, s32 p3, f32 fa0)
{
    s32 t0;

    AiMoveRunToTarget_2be160(p0, p1, p2, p3, fa0);
    t0 = p1->m00;
    CharaRemoveFlags_212480(t0, 2);
}
