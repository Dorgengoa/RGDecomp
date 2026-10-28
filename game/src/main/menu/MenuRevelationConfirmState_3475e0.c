/* rgp:protos */
#define RGP_SELF_MenuRevelationConfirmState_3475e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_00482E38;
extern u8 D_004B2570[0x400];

s32 MenuRevelationConfirmState_3475e0(void)
{
    s32 temp_16;

    temp_16 = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if (temp_16 == 1) {
        D_00482E38 = 1;
        UiFadeWidgetAlpha_290690(D_00482360, 0x5A, 0.0f, D_0047D5D0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5C, 0.0f, D_0047D5D0, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x75, 0);
    } else if (temp_16 == 2) {
        D_00482E38 = 0;
        StateMachineSetState_28ede0(D_0048235C, 0x75, 0);
    }
    return 1;
}
