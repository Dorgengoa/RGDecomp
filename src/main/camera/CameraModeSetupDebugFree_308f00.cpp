/* PARK s16d: 2 round trips tried, length 0xD4 vs retail 0xD0 (1 word over)
   in both. First arm and a local-decl-order swap (v16 declared last) scored
   identically -- register colouring for arg0/v16 across the two vtable
   calls is s0=arg0,s1=v16 here vs retail's s0=v16,s1=arg0; decl-order sweep
   didn't flip it. Extra word not yet localised past that. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern "C" {

extern s64 CameraModeGetCurrent_309370(void);
extern void *GetGameData_1fede0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern void CharaGetPos_2388a0(s32, void *);
extern void CameraChaseStep_161b60(void *, f32);

class VC_0 {
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
    virtual void d20();
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
    virtual void f(void * x0);
};
class VC_1 {
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
    virtual void d20();
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
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void f(void * x0);
};
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
};
void CameraModeSetupDebugFree_308f00(void *arg0)
{
    u8 sp40[0x10];
    u8 sp30[0x10];
    s32 v2;
    s8 mode;
    void *vtbl;
    void *v16;

    mode = (s8)CameraModeGetCurrent_309370();
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
