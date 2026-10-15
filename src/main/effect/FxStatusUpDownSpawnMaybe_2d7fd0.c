#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetParamInt_2e0530(s32, void *, s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004616B0[];

void FxStatusUpDownSpawnMaybe_2d7fd0(s32 p0)
{
    u128 v30[2];
    s32 r0;

    r0 = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(v30, r0, D_004616B0, -1);
    EffectSetId_2e0100(r0, v30, p0);
    EffectSetParamInt_2e0530(r0, v30, 0, 0);
}
