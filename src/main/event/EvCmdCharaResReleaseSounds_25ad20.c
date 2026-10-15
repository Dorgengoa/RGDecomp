#include "types.h"

extern s32 GetCharaResMgr_1fdb60(void);
extern s32 CharaResReleaseSounds_1effa0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdCharaResReleaseSounds_25ad20(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCharaResMgr_1fdb60();
    r1 = CharaResReleaseSounds_1effa0(r0);
    return 1;
}
