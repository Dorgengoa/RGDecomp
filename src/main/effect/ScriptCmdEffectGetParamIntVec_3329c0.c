#include "types.h"

s32 EffectInstanceGetParamIntVec_2dd5c0(s32, s32, s32 *);
s32 ScriptSlotStoreIntRef_3347f0(s32, s32);
s32 ScriptSlotGetInt_3348b0(s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamIntVec_3329c0(s64 *arg0, s32 arg1) {
    s32 buf[4];
    s32 v;

    if (arg1 < 4 || arg1 > 6) {
        return 0;
    }
    v = 0;
    switch (arg1) {
    case 4:
    case 5:
        v = D_004826E0;
        break;
    case 6:
        v = D_004826E0;
        break;
    }
    EffectInstanceGetParamIntVec_2dd5c0(v, ScriptSlotGetInt_3348b0((s32)arg0++), buf);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, buf[0]);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, buf[1]);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, buf[2]);
    if (arg1 > 4) {
        ScriptSlotStoreIntRef_3347f0((s32)arg0, buf[3]);
    }
    return 1;
}
