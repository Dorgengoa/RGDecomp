/* rgp:protos */
#define RGP_SELF_AiCmdEffectSetId_2c2140 1
#include "port/game_protos.h"
#line 1
/* AiCmdEffectSetId_2c2140 -- shape-identical to merged CaptionCfgCmdSetAltCellSize_33ed50 (23 instructions); the donor's
   source with the symbol renamed and 3 call target(s) substituted:
     VariantGetInt_15f780 -> ScriptSlotGetInt_2cc9c0
     CaptionCfgSetAltCellSize_3401e0 -> EffectSetIdById_2e0080
     GetCaptionCfg_340430 -> GetEffectMgr_2d9040
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Two-operand script-command handler.  Cursor is a post-incremented 8-byte
   operand pointer (see CaptionCfgCmdSetGlyphOrigin_33ec50.c). */

typedef struct SArg {
    s32 w[2];
} SArg;

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdEffectSetId_2c2140(SArg *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetEffectMgr_2d9040());
    r1 = ScriptSlotGetInt_2cc9c0(p0++);
    r2 = ScriptSlotGetInt_2cc9c0(p0);
    EffectSetIdById_2e0080(r0, r1, r2);
    return 1;
}
