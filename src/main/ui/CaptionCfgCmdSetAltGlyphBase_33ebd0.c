#include "types.h"

extern s32 GetCaptionCfg_340430(void);
extern s32 VariantGetInt_15f780(s32);
extern s32 CaptionCfgSetAltGlyphBase_33fe50(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCfgCmdSetAltGlyphBase_33ebd0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetCaptionCfg_340430();
    r1 = VariantGetInt_15f780(p0);
    r2 = CaptionCfgSetAltGlyphBase_33fe50(r0, r1);
    return 1;
}
