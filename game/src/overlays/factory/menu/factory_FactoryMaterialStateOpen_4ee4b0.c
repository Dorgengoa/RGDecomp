/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialStateOpen_4ee4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Meta { u8 pad00[0x14]; s16 f14; s16 f16; } Meta;
typedef struct Win  { u8 pad00[0x20]; void *f20; } Win;

typedef struct Root {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    void *f48;
} Root;

extern Root *D_00484A58;
extern f32   D_0047D278;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialStateOpen_4ee4b0(s32 a, s32 b)
{
    Meta *m;
    Win  *q;

    if (b != 0) {
        UiSetWidgetVisible_290010(D_00484A58->f40, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(4);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        UiSetWidgetVisible_290010(D_00484A58->f40, 0xB0, 1, -1);
        UiSetWidgetVisible_290010(D_00484A58->f40, 0x6D, 0, -1);
        UiSetWidgetVisible_290010(D_00484A58->f40, 0x77, 0, -1);
        UiSetWidgetVisible_290010(D_00484A58->f40, 0x67, 0, -1);
        factory_FactoryMaterialCursorReset_4f3fa0(D_00484A58);
        q = ((Win *)UiFindWidget_290460(D_00484A58->f40, 0x5D));
        if (q != 0) {
            if (q->f20 != 0) {
                UiLayoutPanelFrame_28d580(q->f20, 0, 0, 0x193, 0x96, 0);
            }
        }
        UiSetWidgetPos_290f60(D_00484A58->f40, 0xB0, 0x200, 0xAF);
        UiMoveWidgetUniform_290f50(D_00484A58->f40, 0xB0, 0x2F, 0xAF, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(D_00484A58->f40, 0xB0, 1.0f, 0.125f, 0.0f);
        m = ((Meta *)UiEntryListFindByTag_28ea40(D_00484A58->f44, 0x891C));
        m->f16 = 0;
        m->f14 = 0;
        factory_FactoryMaterialTabHighlight_4f3740(D_00484A58);
        factory_FactoryMaterialFrameInit_4f3d80(D_00484A58);
        factory_FactoryMaterialLayout_4f3e00(D_00484A58);
        factory_FactoryMaterialShowCellInfo_4f38f0(D_00484A58);
    }
    StateMachineSetState_28ede0(D_00484A58->f48, 0x8980, 0);
    return 1;
}
