#include "types.h"
#include "vec.h"

extern "C" {
extern void *ObjRecGetLiveObject_1c3bc0(void *, s32);
extern void VecSub_1cbd00(u128 *, u128 *, void *);
extern void VecAdd_1cbdc0(u128 *, u128 *, void *);
extern void ScreenFadeCaptureFrame_1cf550(void *);
extern void ScreenFadeDissolveIn_1cf720(void *, s32, f32);
extern void ScreenFadeReset_1cf760(void *);
extern void *GetCurrentScene_1f5be0(void);
extern void PartyUpdateLeaderFlags_1fc3c0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern void CharaDropHeldTarget_211de0(s32, s32);
extern void CharaRebindModelResetMaybe_212e20(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(s32, void *);
extern void GameDataLatchLeaderId_2f38e0(void);
extern void TargetMngClearTarget_313c00(void);
extern void sceVu0CopyVector(void *, u128 *);
extern s32 D_00482780;
}

class Obj {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vA4(u128 * a0) { VCM(void, (void *, u128 *), 0xA4, a0); }
    void vA8(u128 * a0) { VCM(void, (void *, u128 *), 0xA8, a0); }
    
    
    
    
    
    
    
    void vC8(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
};

extern "C" void PartyApplyLeaderChange_2f36f0(void)
{
    u128 sp80;
    u128 sp70;
    u8 sp60[0x10] __attribute__((aligned(16)));
    void *mgr;
    Obj *obj;
    s32 world;
    s32 a;
    s32 b;
    s32 cur;
    s32 prev;

    cur = *(s16 *)(*(u8 **)((u8 *)GetGameData_1fede0() + 0x18) + 0x18E);
    prev = D_00482780;
    if (cur == prev) return;
    mgr = GetCurrentScene_1f5be0();
    obj = (Obj *)ObjRecGetLiveObject_1c3bc0(mgr, *(s32 *)((u8 *)mgr + 0x4344));
    if (obj == NULL) return;
    obj->vA4(&sp80);
    obj->vA8(&sp70);
    world = GetActionMgr_1fdb50();
    a = ActionMgrFindById_233b50(world, prev);
    if (a != 0) {
        CharaRebindModelResetMaybe_212e20(a);
        CharaDropHeldTarget_211de0(a, 0);
    }
    b = ActionMgrFindById_233b50(world, cur);
    if (b != 0) {
        CharaRebindModelResetMaybe_212e20(b);
        CharaDropHeldTarget_211de0(b, 0);
    }
    if (a != 0 && b != 0) {
        CharaGetPos_2388a0(a, sp60);
        VecSub_1cbd00(&sp80, &sp80, sp60);
        VecSub_1cbd00(&sp70, &sp70, sp60);
        CharaGetPos_2388a0(b, sp60);
        VecAdd_1cbdc0(&sp80, &sp80, sp60);
        VecAdd_1cbdc0(&sp70, &sp70, sp60);
        *(u128 *)((u8 *)obj + 0x60) = sp80;
        *(u128 *)((u8 *)obj + 0xF0) = sp80;
        sceVu0CopyVector((u8 *)obj + 0x1C0, &sp70);
        *(u128 *)((u8 *)obj + 0x50) = sp70;
        *(u128 *)((u8 *)obj + 0xE0) = sp70;
        obj->vC8(1.0f);
        ScreenFadeReset_1cf760(mgr);
        ScreenFadeCaptureFrame_1cf550(mgr);
        ScreenFadeDissolveIn_1cf720(mgr, 0xF, 1.0f);
    }
    TargetMngClearTarget_313c00();
    PartyUpdateLeaderFlags_1fc3c0();
    GameDataLatchLeaderId_2f38e0();
}
