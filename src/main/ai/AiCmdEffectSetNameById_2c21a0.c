#include "types.h"

/* Two-operand script-command handler.  Cursor is a post-incremented 8-byte
   operand pointer (see CaptionCfgCmdSetGlyphOrigin_33ec50.c). */

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 GetEffectMgr_2d9040(void);
extern s32 ScriptSlotGetInt_2cc9c0(SArg *);
extern s32 ScriptSlotGetCodeAddr_2cc980(SArg *);
extern s32 EffectSetNameById_2e0140(s32, s32, s32);

s32 AiCmdEffectSetNameById_2c21a0(SArg *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetEffectMgr_2d9040();
    r1 = ScriptSlotGetInt_2cc9c0(p0++);
    r2 = ScriptSlotGetCodeAddr_2cc980(p0);
    EffectSetNameById_2e0140(r0, r1, r2);
    return 1;
}
