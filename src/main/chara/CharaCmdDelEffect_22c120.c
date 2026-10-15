#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectReleaseNodesByKey_2e1250(s32, s32, s64);
extern void EffectReleaseByKey_2e1260(s32, s32);
extern s64 ScriptArgGetInt_302d70(s32);

s32 CharaCmdDelEffect_22c120(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;

    if ((arg2 != 0) && (arg2 != 1)) {
        return 0;
    }
    temp_16 = GetEffectMgr_2d9040();
    switch (arg2) {
    case 0:
        EffectReleaseByKey_2e1260(temp_16, *arg0);
        break;
    case 1:
        EffectReleaseNodesByKey_2e1250(temp_16, *arg0, (s64) (s16) ScriptArgGetInt_302d70(arg1));
        break;
    }
    return 1;
}
