/* rgp:protos */
#define RGP_SELF_MenuWeaponCombinePairConfirmStateMaybe_2aada0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct U_002aada0 {
    u8 pad0[0x10];
    s16 f10;
} U_002aada0;

extern s32 D_00482364;
extern s32 D_00482360;
extern s32 D_0048235C;
extern s32 D_00482384;
extern u8 D_004B2570[];
extern f32 D_0047D750;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuWeaponCombinePairConfirmStateMaybe_2aada0(s32 a, s32 flag)
{
    s32 r;
    s32 t;
    U_002aada0 *u;
    s32 v;
    if (flag != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0xC, 1);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    u = ((U_002aada0 *)UiEntryListGetCurrentData_28ec60(D_00482364));
    t = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(t);
    MenuWeaponCombineAnimTickMaybe_361cd0(t);
    if (r == 1) {
        v = u->f10;
        if (v == 0) {
            StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.5f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x137, 0.0f, D_0047D750, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0x23, 0);
        } else if (v == 1) {
            StateMachineSetState_28ede0(D_0048235C, 0x22, 0);
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x22, 0);
    }
    return 1;
}
