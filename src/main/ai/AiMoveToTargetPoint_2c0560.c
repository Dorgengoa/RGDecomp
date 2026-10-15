#include "types.h"

extern void AiGetTargetPoint_2c0fe0(s32, void *);
extern void AiRouteMoveToPosMaybe_2beed0(s32, s32, void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void AiMoveToTargetPoint_2c0560(s32 p0, s32 p1)
{
    u128 v30;

    AiGetTargetPoint_2c0fe0(p0, &v30);
    AiRouteMoveToPosMaybe_2beed0(p0, p1, &v30, 0);
}
