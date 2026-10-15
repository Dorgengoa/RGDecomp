#include "types.h"

extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectAttachToNode_2e0790(s32, void *, s32);
extern void EffectCreateByName_2e1020(void *, s32, s32, s32);
extern void EffectSetAutoRelease_2e1170(s32, void *, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 ScriptArgGetInt_302d70(s32);

s32 CharaCmdFlameThrower_228ea0(s32 *arg0, s32 arg1, s32 arg2) {
    u8 sp50[0x20];
    s32 temp_2;
    s32 a;
    s32 id;

    if (arg2 != 3) {
        return 0;
    }
    a = ScriptArgGetInt_302d70(arg1);
    temp_2 = GetObjNodeByName_1ce3a0(*arg0, a, ScriptArgGetStr_302cb0(arg1 + 5));
    if (temp_2 == 0) {
        return 1;
    }
    id = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(sp50, id, ScriptArgGetStr_302cb0(arg1 + 0xA), -1);
    EffectSetAutoRelease_2e1170(id, sp50, 1);
    EffectSetId_2e0100(id, sp50, *arg0);
    EffectAttachToNode_2e0790(id, sp50, temp_2);
    return 1;
}
