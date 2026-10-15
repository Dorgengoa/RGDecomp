#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 MenuFadeStep_29ffd0(s32, f32);
extern void MenuFadeStartFromColor_2a0020(s32);
extern s32 MapMgrAuxAreaIsLoaded_389e10(void);
extern void InsectCageLoadMap_389e70(s32);
extern s32 InsectCageMenuSetup_38a820(void);
extern void InsectCageMenuRequestLoads_38ab70(void);
extern void InsectCageMenuResetAll_38b0d0(void);
extern s32 InsectCageGetType_3910c0(void);
extern s32 D_0048235C;
extern s32 D_00482374;
extern s8 D_00482508;

s32 InsectCageMenuLoadStep_2a8c50(s32 arg0, s32 arg1)
{
    if (arg1 != 0) {
        D_00482508 = 0;
    }
    GetLoaderMgr_1f59d0();
    switch (D_00482508) {
    case 0:
        if (MenuFadeStep_29ffd0(D_00482374, 1.0f) != 0) {
            InsectCageMenuResetAll_38b0d0();
            InsectCageLoadMap_389e70(InsectCageGetType_3910c0());
            D_00482508 += 1;
        }
        break;
    case 1:
        if (MapMgrAuxAreaIsLoaded_389e10() != 0) {
            D_00482508 += 1;
        }
        break;
    case 2:
        InsectCageMenuRequestLoads_38ab70();
        D_00482508 += 1;
        break;
    case 3:
        if (InsectCageMenuSetup_38a820() != 0) {
            MenuFadeStartFromColor_2a0020(D_00482374);
            D_00482508 += 1;
        }
        break;
    case 4:
        if (MenuFadeStep_29ffd0(D_00482374, 1.0f) != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0xAC, 0);
        }
        break;
    }
    return 1;
}
