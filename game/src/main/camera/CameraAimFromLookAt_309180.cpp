#include "types.h"
extern "C" {

extern f32 Atan2f_1291a8(f32 arg0, f32 arg1);
extern void CameraChaseStep_161b60(void *arg0, f32 arg1);
extern f32 VecLengthXZ_1cb490(f32 *arg0);
extern void VecSub_1cbd00(f32 *arg0, void *arg1, void *arg2);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern void CharaResetBattleStateMaybe_212f20(s32 arg0, s32 arg1);
extern s32 ActionMgrFindById_233b50(s32 arg0, s16 arg1);

class VC_2 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void g39(void * a0) { VCM(void, (void *, void *), 0xA4, a0); }
    void g40(void * a0) { VCM(void, (void *, void *), 0xA8, a0); }
};
void CameraAimFromLookAt_309180(void *arg0)
{
    u8 sp50[0x10] __attribute__((aligned(16)));
    u8 sp40[0x10] __attribute__((aligned(16)));
    f32 sp30[4] __attribute__((aligned(16)));
    s32 temp_2;
    void *temp_16;
    void *vtbl;

    temp_16 = GetGameData_1fede0();
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)((u8 *)(*(s32 *)((u8 *)temp_16 + 0x18)) + 0x18E));
    if (temp_2 != 0) {
        CharaResetBattleStateMaybe_212f20(temp_2, 0);
        ((VC_2 *)(arg0))->g40(sp40);
        ((VC_2 *)(arg0))->g39(sp50);
        VecSub_1cbd00(sp30, sp40, sp50);
        *(f32 *)((u8 *)arg0 + 0x2A4) = Atan2f_1291a8(sp30[0], sp30[2]);
        *(f32 *)((u8 *)arg0 + 0x2A8) = Atan2f_1291a8(sp30[1], VecLengthXZ_1cb490(sp30));
        ((VC_2 *)(arg0))->f();
        CameraChaseStep_161b60(arg0, 1.0f);
    }
}

}
