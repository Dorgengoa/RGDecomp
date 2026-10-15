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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void f();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void g39(void *);
    virtual void g40(void *);
};
void CameraAimFromLookAt_309180(void *arg0)
{
    u8 sp50[0x10];
    u8 sp40[0x10];
    f32 sp30[4];
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
