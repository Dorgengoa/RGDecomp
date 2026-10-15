#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 EffectKillById_2e0640(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdEffectKill_2c2100(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetEffectMgr_2d9040();
    r1 = ScriptSlotGetInt_2cc9c0(p0);
    r2 = EffectKillById_2e0640(r0, r1);
    return 1;
}
