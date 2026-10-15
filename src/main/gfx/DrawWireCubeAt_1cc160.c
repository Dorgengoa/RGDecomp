#include "types.h"

extern void MatFromPosScale_1cb2b0(void *, s32, f32);
extern void DrawWireCube_1cc1b0(s32, void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawWireCubeAt_1cc160(s32 p0, s32 p1, s32 p2, f32 fa0)
{
    u128 v30[4];

    MatFromPosScale_1cb2b0(v30, p1, fa0);
    DrawWireCube_1cc1b0(p0, v30, p2);
}
