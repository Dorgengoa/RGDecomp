/* rgp:protos */
#define RGP_SELF_MenuInsectCageExitState_2a8ad0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK s16d: 1 round trip, same length as retail (87 words) but 53 bad --
   likely a register-colouring/CSE residue, not a structural one. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048235C;
extern s32 D_00482360;
extern void *D_00482374;
extern s32 D_0048250C;

s32 MenuInsectCageExitState_2a8ad0(s32 pad0, s32 arg1)
{
    s32 t16;
    void *t2;

    if (arg1 != 0) {
        D_0048250C = 0;
        MenuFadeStartToColor_2a0040(D_00482374);
    }
    if (MenuFadeStep_29ffd0(D_00482374, 1.0f) == 1) {
    if (D_0048250C == 0) {
        InsectCageMenuClose_38af10();
        FieldViewModeBegin_202f10();
        t16 = *(s32 *)((u8 *)GetCurrentScene_1f5be0() + 0x4348);
        t2 = GetCurrentScene_1f5be0();
        *(s32 *)((u8 *)t2 + 0x4348) = *(s32 *)((u8 *)t2 + 0x4344);
        *(s32 *)((u8 *)t2 + 0x4344) = t16;
        *(s16 *)((u8 *)D_00482374 + 0x46) = 0;
        MenuFadeSetColor_29ff90(D_00482374, 8, 8, 8);
        MenuFadeStartFromColor_2a0020(D_00482374);
        MenuSetWidgetGroupVisible_2a8ab0(1);
        UiSetWidgetsVisibleById_291110(D_00482360, 3, 1, 1);
        UiSetWidgetVisible_290010(D_00482360, 0x8A, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6C, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6B, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x71, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 0, 1);
    } else {
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    D_0048250C += 1;
    }
    return 1;
}
