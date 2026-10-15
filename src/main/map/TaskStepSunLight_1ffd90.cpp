/* MATCH (s41a5): MapFindBlockAtPos_1e3a00's third parameter is a FLOAT (retail writes
   $f12 = 0.0f, never $a2), and the sp70 buffer is passed directly. */
#include "types.h"
#include "vec.h"
#pragma opt_propagation off
extern "C" {

extern s32 ObjRecGetLiveObject_1c3bc0(void *, s32);
extern s32 MapFindBlockAtPos_1e3a00(s32, void *, f32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern void *MapAreaGetLightSetOrDefault_1e5430(s32, s32, s32);
extern s32 MapDataIsGlare_1e7b00(s32);
extern void *GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern void *GetMapSunLight_201a30(void);
extern s32 GetMapMgr_201a90(void);
extern s32 CharaGetAreaId_213c90(s32);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern s32 CharaGetGroundAttr_238310(s32);
extern s32 EvtCurIsRunning_26abf0(void);
extern void SunLightUpdate_293bd0(void *);

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
void TaskStepSunLight_1ffd90(void)
{
        void * arg_h1;

    u8 sp70[0x10];
    void *temp_20;
    s32 temp_2_3;
    void *var_19;
    s32 temp_18;
    s32 var_17;
    void *temp_21;
    void *temp_2;
    void *temp_2_2;
    u16 var_16;

    temp_20 = GetMapSunLight_201a30();
    var_19 = NULL;
    temp_21 = GetGameData_1fede0();
    temp_18 = GetMapMgr_201a90();
    var_17 = 0;
    var_16 = 0;
    if (EvtCurIsRunning_26abf0() != 0) {
        temp_2 = GetCurrentScene_1f5be0();
        temp_2_2 = (void *)ObjRecGetLiveObject_1c3bc0(temp_2, *(s32 *)((u8 *)temp_2 + 0x4344));
        ((VC_0 *)(temp_2_2))->f(sp70);
        arg_h1 = sp70;
        var_17 = MapFindBlockAtPos_1e3a00(temp_18, sp70, 0.0f);
        var_16 = 1;
    } else {
        temp_2_3 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)((u8 *)(*(void **)((u8 *)temp_21 + 0x18)) + 0x18E));
        if (temp_2_3 != 0) {
            var_17 = MapSlotsFindBlockById_1e49b0(temp_18, CharaGetAreaId_213c90(temp_2_3), 0);
            var_16 = CharaGetGroundAttr_238310(temp_2_3) < 8;
        }
    }
    if ((var_17 != 0) && (MapDataIsGlare_1e7b00(var_17) != 0) && (var_16)) {
        var_19 = MapAreaGetLightSetOrDefault_1e5430(temp_18, var_17, 0);
    }
    if (var_19 != NULL) {
        *(u128 *)((u8 *)temp_20 + 0x30) = *(u128 *)((u8 *)var_19 + 0x30);
        *(s8 *)((u8 *)temp_20 + 0x1) = 1;
        *(s32 *)((u8 *)temp_20 + 0x4C) = 0;
    } else {
        *(s32 *)((u8 *)temp_20 + 0x4C) = 1;
    }
    SunLightUpdate_293bd0(temp_20);
}

}
