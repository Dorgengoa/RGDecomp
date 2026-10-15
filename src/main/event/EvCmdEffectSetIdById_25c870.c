/* EvCmdEffectSetIdById_25c870 -- shape-identical to merged CaptionCfgCmdSetAltCellSize_33ed50 (23 instructions); the donor's
   source with the symbol renamed and 3 call target(s) substituted:
     VariantGetInt_15f780 -> ScriptGetInt_26a2a0
     CaptionCfgSetAltCellSize_3401e0 -> EffectSetIdById_2e0080
     GetCaptionCfg_340430 -> GetEffectMgr_2d9040
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Two-operand script-command handler.  Cursor is a post-incremented 8-byte
   operand pointer (see CaptionCfgCmdSetGlyphOrigin_33ec50.c). */

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 GetEffectMgr_2d9040(void);
extern s32 ScriptGetInt_26a2a0(SArg *);
extern s32 EffectSetIdById_2e0080(s32, s32, s32);

s32 EvCmdEffectSetIdById_25c870(SArg *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetEffectMgr_2d9040();
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = ScriptGetInt_26a2a0(p0);
    EffectSetIdById_2e0080(r0, r1, r2);
    return 1;
}
