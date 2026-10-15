#include "types.h"

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern s32 D_00483590;
extern s32 D_00483594;
extern s16 D_00483598;
extern f32 D_0047D5C8;

extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern void *UiGetWidgetSprite_28fe10(void *o, s32 id, s32 a);
extern void UiLayoutPanelFrame_28d580(void *w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void UiSetSpriteSizeUvSize_28f670(void *o, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void UiSetSpriteScaleToSize_28fb10(void *o, s32 id, s32 a, s32 b, s32 c);
extern void UiSetWidgetVisible_290010(void *o, s32 id, s32 a, s32 b);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern void UiMoveWidgetUniform_290f50(void *o, s32 id, s32 x, s32 y, s32 z, f32 t);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void UiEntryListSelectByTag_28ea90(void *o, s32 id, s32 a);
extern s16 *UiEntryListFindByTag_28ea40(void *o, s32 id);
extern void InfoEdgeMenuLoadRequest_398990(void);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 InfoEdgeListOpen_399ce0(s32 unused, s32 en)
{
    void *w;
    s16 *r;

    if (en != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x65, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x76, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6B, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x69, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x68, 0, 1);
        w = UiGetWidgetSprite_28fe10(D_00482360, 0x212, 0);
        if (w != 0) {
            UiLayoutPanelFrame_28d580(w, 0, 0, 0x19D, 0x14F, 0);
        }
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x212, 0, 0, 0, 0, 0);
        UiSetSpriteScaleToSize_28fb10(D_00482360, 0x210, 0x17F, 0x12E, 0);
        UiSetSpriteScaleToSize_28fb10(D_00482360, 0x211, 0x17F, -0x270F, 0);
        UiSetWidgetVisible_290010(D_00482360, 0x20F, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x20F, 0x200, 0x4B);
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x5A, 0x4B, 0, D_0047D5C8);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 1, 1);
        D_00483594 = 0;
        D_00483590 = 0;
        D_00483598 = 0;
        UiEntryListSelectByTag_28ea90(D_00482364, 0xE, 1);
        r = UiEntryListFindByTag_28ea40(D_00482364, 0xE);
        UiSetWidgetPos_290f60(D_00482360, 0x219, r[2], r[3]);
        InfoEdgeMenuLoadRequest_398990();
    }
    StateMachineSetState_28ede0(D_0048235C, 0xA7, 0);
    return 1;
}
