#include "types.h"
#include "vec.h"

class O308 {
public:
    u8 pad0[0xC0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void f58();
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void w31();
    virtual void w32();
    virtual void w33();
    virtual void w34();
    virtual void w35();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void w43();
    virtual void w44();
    virtual void w45();
    virtual void w46();
    virtual void w47();
    virtual void fC8(f32);
};

extern "C" {
void CameraSetLag_177170(void *, f32, f32);
void *CharaResFindById_1f0530(s32, s32);
s32 GetCharaResMgr_1fdb60(void);
void *GetGameData_1fede0(void);
void CameraModeLockTargetUpdateMaybe_3062e0(void *, s32);
void CameraResetParams_3090a0(void *, s32);
s32 CharaSysGetEncounterIdMaybe_3a36d0(s32);
extern u8 D_004E7270[0x400];
extern u8 D_004E7280[0x400];
extern u8 D_004E7290[0x400];
extern u8 D_004E7294[0x400];
extern u8 D_004E7298[0x400];
extern u8 D_004E729C[0x400];
extern u8 D_004E72A0[0x400];
extern u8 D_004E72A4[0x400];
extern u8 D_004E72A8[0x400];
extern u8 D_004E72A9[0x400];
extern u8 D_004E72AA[0x400];
}

extern "C" void CameraModeSetupLockTargetMaybe_308ae0(O308 *arg0, s32 arg1)
{
    u8 *g;
    u8 *p;
    s32 x;
    s32 r;

    g = (u8 *)GetGameData_1fede0();
    CameraResetParams_3090a0(arg0, arg1);
    *(u128 *)D_004E7270 = 0;
    *(u128 *)D_004E7280 = 0;
    *(s8 *)D_004E7290 = 0;
    *(s32 *)D_004E7294 = 0;
    *(s32 *)D_004E7298 = 0;
    *(s32 *)D_004E729C = 0;
    *(s32 *)D_004E72A0 = 1;
    *(s32 *)D_004E72A4 = 1;
    *(s8 *)D_004E72A8 = 0;
    *(s8 *)D_004E72A9 = 0;
    *(s8 *)D_004E72AA = 1;
    CameraSetLag_177170(arg0, 1.0f, 1.0f);
    arg0->f58();
    CameraModeLockTargetUpdateMaybe_3062e0(arg0, arg1);
    arg0->fC8(1.0f);
    CameraSetLag_177170(arg0, 2.5f, 4.0f);
    *((u8 *)arg0 + 0x2E0) = 1;
    p = (u8 *)CharaResFindById_1f0530(GetCharaResMgr_1fdb60(), 0x80);
    if (p != 0) {
        x = *(s16 *)(p + 2);
        if (x == 0x2EFF) {
            *(s8 *)D_004E72A8 = 1;
        }
        if ((u32)(x - 0x30EF) < 2) {
            *(s8 *)D_004E72A9 = 1;
        }
    }
    r = CharaSysGetEncounterIdMaybe_3a36d0(*(s32 *)(g + 0x20));
    if (r == 0x3EC || r == 0x3ED || r == 0x3EE || r == 0x3F4 || r == 0x3F5 || r == 0x3F8 || r == 0x3FF || r == 0x403 ||
        r == 0x404 || r == 0x2712 || r == 0x2713 || r == 0x2714 || r == 0x2717 || r == 0x2718 || r == 0x2719 || r == 0x271B) {
        *(s8 *)D_004E72AA = 0;
    }
}
