#include "types.h"

extern s32 FarClipRecParseArgs_18c850(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0049D080[];

s32 MapCfgMapFarClip_18bdd0(s32 p0, s32 p1)
{
    s32 r;

    r = FarClipRecParseArgs_18c850(D_0049D080, p0, p1);
    return 1;
}
