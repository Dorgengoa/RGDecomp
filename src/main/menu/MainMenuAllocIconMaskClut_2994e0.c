#include "types.h"

extern s32 MemStackAlloc1K_28c2a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482334;
extern s32 D_0048234C;

s32 MainMenuAllocIconMaskClut_2994e0(void)
{
    s32 r;

    r = MemStackAlloc1K_28c2a0(D_00482334);
    D_0048234C = r;
    return r;
}
