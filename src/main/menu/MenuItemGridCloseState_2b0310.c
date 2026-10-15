#include "types.h"

extern u8 *GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern s32 InvObjCastToItem4B0_3d3cd0(s32);
extern void CageRecRollCatchesMaybe_3e8510(u8 *, s32);
extern s32 WorldDataMgrNoRequestPending_3eef10(s32);
extern void WorldDataRequestKind_3f0960(s32, s32);
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

    temp_18 = GetGameData_1fede0();
    temp_17 = GetWorldDataMgr_1fedf0();
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
                t = InvFindInCategoryRange_3c8370(*(s32 *)(temp_18 + 0x18), *(s32 *)(D_00482374 + 0x6C), 0, -1, 0, 0);
                if (t != 0) {
                    t = InvObjCastToItem4B0_3d3cd0(t);
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
