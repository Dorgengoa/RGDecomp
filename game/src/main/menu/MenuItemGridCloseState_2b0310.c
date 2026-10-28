/* rgp:protos */
#define RGP_SELF_MenuItemGridCloseState_2b0310 1
#include "port/game_protos.h"
#line 1
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
extern f32 D_0047D764;
extern f32 D_0047D768;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 *D_00482374;

s32 MenuItemGridCloseState_2b0310(s32 arg0, s32 arg1)
{
    u8 *temp_18;
    s32 temp_17;
    s32 i;
    s32 t;

    temp_18 = ((u8 *)GetGameData_1fede0());
    temp_17 = ((s32)GetWorldDataMgr_1fedf0());
    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x7E, 0.0f, D_0047D764, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 0.0f, D_0047D764, -1.0f);
        for (i = 0; i < 6; i++) {
            UiFadeWidgetAlpha_290690(D_00482360, (i + 0x83) & 0xFFFF, 0.0f, D_0047D764, -1.0f);
        }
        if (*(s16 *)(D_00482374 + 0x70) != 0) {
            WorldDataRequestKind_3f0960(temp_17, 4);
        }
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D768, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D768, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0x83) <= 0.0f) {
        if (*(s16 *)(D_00482374 + 0x70) != 0) {
            if (WorldDataMgrNoRequestPending_3eef10(temp_17) != 0) {
                t = ((s32)InvFindInCategoryRange_3c8370(*(s32 *)(temp_18 + 0x18), *(s32 *)(D_00482374 + 0x6C), 0, -1, 0, 0));
                if (t != 0) {
                    t = ((s32)InvObjCastToItem4B0_3d3cd0(t, 0, 0, 0));
                    if (t != 0) {
                        CageRecRollCatchesMaybe_3e8510(temp_18, t);
                    }
                }
                StateMachineSetState_28ede0(D_0048235C, 0xA, 1);
            }
        } else {
            StateMachineSetState_28ede0(D_0048235C, 9, 0);
        }
    }
    return 1;
}
