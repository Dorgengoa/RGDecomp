#include "types.h"

extern void ActTimeMoveGetOffset_2277a0(s32, void *, f32, f32);
extern void VecAdd_1cbdc0(s32, s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ActTimeMoveAddOffset_227760(s32 p0, s32 p1, f32 fa0, f32 fa1)
{
    u128 v20;

    ActTimeMoveGetOffset_2277a0(p0, &v20, fa0, fa1);
    VecAdd_1cbdc0(p1, p1, &v20);
}
