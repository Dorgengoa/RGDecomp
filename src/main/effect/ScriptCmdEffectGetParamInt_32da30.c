#include "types.h"

typedef struct Buf { u8 b[0x1C]; } Buf;
extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(Buf *, s32);
extern void EffectGetParamInt_2e0420(s32, Buf *, s32, s32 *);
extern void ScriptSlotStoreIntRef_3347f0(s32, s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamInt_32da30(s64 *arg0, s32 arg1) {
    s32 sp5C;
    Buf sp40;
    s32 t;
    s32 obj;
    s32 p;

    if (arg1 != 2 && arg1 != 3) {
        return 0;
    }
    p = 0;
    switch (arg1) {
    case 2:
    case 3:
        p = D_004826E0;
        break;
    }
    if (p == 0) {
        return 0;
    }
    sp5C = 0;
    t = ScriptSlotGetInt_3348b0((s32)arg0++);
    if (D_004826E0 == 0) {
        return 0;
    }
    obj = GetEffectMgr_2d9040();
    if (obj == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(&sp40, D_004826E0);
    EffectGetParamInt_2e0420(obj, &sp40, t, &sp5C);
    ScriptSlotStoreIntRef_3347f0((s32)arg0, sp5C);
    return 1;
}
