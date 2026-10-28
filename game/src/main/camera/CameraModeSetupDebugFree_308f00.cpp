/* rgp:protos */
#line 1
/* PARK s16d: 2 round trips tried, length 0xD4 vs retail 0xD0 (1 word over)
   in both. First arm and a local-decl-order swap (v16 declared last) scored
   identically -- register colouring for arg0/v16 across the two vtable
   calls is s0=arg0,s1=v16 here vs retail's s0=v16,s1=arg0; decl-order sweep
   didn't flip it. Extra word not yet localised past that. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern "C" {

extern int CameraModeGetCurrent_309370(void *);
extern void *GetGameData_1fede0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern void CharaGetPos_2388a0(s32, void *);
extern void CameraChaseStep_161b60(void *, f32);

class VC_0 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0xA4, x0); }
};
class VC_1 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0xB0, x0); }
};
class VC_2 {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x58); }
};
void CameraModeSetupDebugFree_308f00(void *arg0)
{
    u8 sp40[0x10] __attribute__((aligned(16)));
    u8 sp30[0x10] __attribute__((aligned(16)));
    s32 v2;
    s8 mode;
    void *vtbl;
    void *v16;

    mode = (s8)CameraModeGetCurrent_309370((void *)arg0);
    if (mode == 9) {
        v16 = GetGameData_1fede0();
        v2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(),
                           *(s16 *)((u8 *)*(void **)((u8 *)v16 + 0x18) + 0x18E));
        if (v2 != 0) {
            CharaGetPos_2388a0(v2, sp40);
            vtbl = *(void **)((u8 *)arg0 + 0xC0);
            ((VC_0 *)(arg0))->f(sp30);
            *(f32 *)(sp30 + 4) = 250.0f + *(f32 *)(sp40 + 4);
            vtbl = *(void **)((u8 *)arg0 + 0xC0);
            ((VC_1 *)(arg0))->f(sp30);
        }
    }
    vtbl = *(void **)((u8 *)arg0 + 0xC0);
    ((VC_2 *)(arg0))->f();
    CameraChaseStep_161b60(arg0, 1.0f);
}

}
