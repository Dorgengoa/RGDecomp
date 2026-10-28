/* rgp:protos */
#define RGP_SELF_CaptionCfgCmdSetGlyphBase_33ec10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCfgCmdSetGlyphBase_33ec10(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetCaptionCfg_340430());
    r1 = VariantGetInt_15f780(p0);
    r2 = (CaptionCfgSetGlyphBase_33fe70(r0, r1), (s32)0);
    return 1;
}
