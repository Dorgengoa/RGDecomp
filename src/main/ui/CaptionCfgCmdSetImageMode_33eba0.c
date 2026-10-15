#include "types.h"

extern s32 GetCaptionCfg_340430(void);
extern s32 CaptionCfgSetImageMode_33fe30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCfgCmdSetImageMode_33eba0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCaptionCfg_340430();
    r1 = CaptionCfgSetImageMode_33fe30(r0, 1);
    return 1;
}
