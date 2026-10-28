/* rgp:protos */
#line 1
#include "types.h"
class Obj { u8 pad[0x1B0]; public: VC_VPTR_MEMBER;void f(f32 a0) { VCM(void, (void *, f32), 0x44, a0); } };
extern "C" {

extern void *ObjRecGetLiveObject_1c4a90(s32, s16);
extern s32 GetCurrentScene_1f5be0(void);
extern void CameraSnapReqAt_1f6d70(s32);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s16 FuncPointGetActiveId_201a00(void);
extern void CharaResetBattleStateMaybe_212f20(s32, s32);
extern void CharaSetPosXYZ_2139e0(s32, f32, f32, f32);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern void * GroupGetRecordById_425590(s32, short);

void LeaderPlaceAtSavePoint_2f1fb0(void)
{
    s32 temp_17;
    s32 temp_18;
    u8 *temp_16;
    u8 *temp_17_2;
    u8 *temp_2;

    temp_16 = (u8 *)GetGameData_1fede0();
    temp_17 = GetCurrentScene_1f5be0();
    temp_18 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(temp_16 + 0x18) + 0x18E));
    temp_17_2 = (u8 *)ObjRecGetLiveObject_1c4a90(temp_17, *(s16 *)(*(u8 **)(temp_16 + 0x18) + 0x18E));
    if ((temp_18 != 0) && (temp_17_2 != NULL)) {
        CharaResetBattleStateMaybe_212f20(temp_18, 0);
        temp_2 = (u8 *)GroupGetRecordById_425590(*(s32 *)(*(u8 **)(temp_16 + 8) + 0x74), (short)(FuncPointGetActiveId_201a00()));
        if (temp_2 != NULL) {
            CharaSetPosXYZ_2139e0(temp_18, *(f32 *)(temp_2 + 0x20), *(f32 *)(temp_2 + 0x24), *(f32 *)(temp_2 + 0x28));
            ((Obj *)temp_17_2)->f(1.0f);
        }
    }
    CameraSnapReqAt_1f6d70(1);
}

}
