#include "types.h"

/* Two-operand script-command handler.  Cursor is a post-incremented 8-byte
   operand pointer (see CaptionCfgCmdSetGlyphOrigin_33ec50.c). */

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 GetEffectMgr_2d9040(void);
extern s32 ScriptGetInt_26a2a0(SArg *);
extern s32 ScriptGetCodeAddr_26a200(SArg *);
extern s32 EffectSetNameById_2e0140(s32, s32, s32);

s32 EvCmdEffectSetNameById_25c8d0(SArg *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetEffectMgr_2d9040();
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = ScriptGetCodeAddr_26a200(p0);
    EffectSetNameById_2e0140(r0, r1, r2);
    return 1;
}
