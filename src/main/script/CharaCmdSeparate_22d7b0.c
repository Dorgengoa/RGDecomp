/* PARK 1/3: length-wrong (76w vs retail 82w), large-ish gap. */
#include "types.h"

void FrameCalcWorldMatrix_148ff0(void *, void *);
void ModelSetRot_151080(s32, void *);
void ModelSetPos_151110(s32, void *);
u8 *ModelGetRootFrame_1511a0(s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
void MatToRotPos_1cade0(void *, void *, void *);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
void CharaSetYaw_2138f0(u8 *, f32);
void CharaSetPos_213a40(u8 *, void *);
u8 *ActionMgrFindById_233b50(s32, s32);
s32 ScriptArgGetInt_302d70(s32);

s32 CharaCmdSeparate_22d7b0(s32 pad0, s32 arg1, s32 arg2) {
    u8 sp50[0x40];
    u8 sp40[16];
    u8 sp30[16];
    s32 temp_16;
    s32 temp_2;
    s32 temp_2_2;
    u8 *temp_2_3;
    u8 *temp_2_4;

    if (arg2 != 1) {
        return 0;
    }
    temp_2 = GetCurrentScene_1f5be0();
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = ObjRecGetLiveObject_1c4a90(temp_2, ScriptArgGetInt_302d70(arg1));
    if (temp_2_2 == 0) {
        return 1;
    }
    if (!(*(s8 *)(ModelGetRootFrame_1511a0(temp_2_2) + 0x28) != 0)) {
        return 1;
    }
    FrameCalcWorldMatrix_148ff0(ModelGetRootFrame_1511a0(temp_2_2), sp50);
    MatToRotPos_1cade0(sp30, sp40, sp50);
    temp_2_3 = ModelGetRootFrame_1511a0(temp_2_2);
    if (*(s8 *)(temp_2_3 + 0x28) != 0) {
        *(s32 *)(temp_2_3 + 4) = 0;
    }
    ModelSetPos_151110(temp_2_2, sp40);
    ModelSetRot_151080(temp_2_2, sp30);
    temp_16 = GetActionMgr_1fdb50();
    temp_2_4 = ActionMgrFindById_233b50(temp_16, ScriptArgGetInt_302d70(arg1));
    if (temp_2_4 != NULL) {
        *(s32 *)(temp_2_4 + 0xA44) = *(s32 *)(temp_2_4 + 0xA44) & 0xFFF7FFFF;
        CharaSetPos_213a40(temp_2_4, sp40);
        CharaSetYaw_2138f0(temp_2_4, *(f32 *)(sp30 + 4));
    }
    return 1;
}
