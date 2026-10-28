/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsStateTick_4ec970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx {
    u8    pad00[0x20];
    void *f20;
    u8    pad24[0x64];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
    void *f94;
    u8    pad98[0x4];
    u8    f9C;
} Ctx;

typedef struct Grid {
    u8    pad00[0x70];
    void *f70;
    u8    pad74[0x1C];
    u8    f90;
} Grid;

typedef struct Msg {
    s32 f0;
} Msg;

extern Ctx  *D_00484A4C;                        /* _gp - 0x724 */
extern Grid *D_00484A48;                        /* _gp - 0x728 */
extern u8 D_004B2570[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryPartsStateTick_4ec970(s32 unused, s32 start)
{
    void *v;
    void *w;
    void *g;
    Ctx  *p;
    Ctx  *c;
    Msg  *m;
    u8    flag;
    s32   r;

    v = D_00484A4C->f8C;
    w = D_00484A4C->f94;
    if (start != 0) {
        UiEntryListSelectByTag_28ea90(D_00484A4C->f90, 0x88F4, 0);
        p = ((Ctx *)UiFindWidget_290460(v, 0x42));
        if (p != 0) {
            if (p->f20 != 0) {
                UiLayoutPanelFrame_28d580(p->f20, 0, 0, 0x95, 0x170, 0);
            }
        }
        g = &D_00484A4C->f9C;
        UiSelFrameReset_28db70(g);
        UiSelFrameInit_28da30(g, v, 0x4B);
        UiSelFrameSetRect_28db40(g, 0x4B, 0x1A, 0x1A, 0x4C, 0x4C, 0, 0);
        UiSelFrameCalcTileCounts_28d9d0(g);
        UiSelFrameSetScrollPeriod_28d9c0(g, 1);
        UiSelFrameSetPos_28daa0(g, 0x4B, 0x1A, 0x1A);
        UiSelFrameAnimStep_28d820(g, 0x4B);
    }
    c = D_00484A4C;
    flag = 0;
    if (c->f88 == 1) {
        flag = 1;
    }
    r = MenuGridCursorInput_28e170(c->f90, D_004B2570, flag, 0);
    if (r == 2 && D_00484A4C->f88 == 0) {
        StateMachineSetState_28ede0(w, 0x891C, 0);
    } else if (r == 2 && D_00484A4C->f88 == 2) {
        factory_FactoryPartsNoStockCloseMaybe_4f0100(D_00484A4C);
    } else if (r == 1) {
        factory_FactoryPartsSelect_4f02c0(D_00484A4C);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0 && D_00484A4C->f88 == 1) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        m = ((Msg *)FactoryGetRequestPtr_367ec0());
        m->f0 = 1;
        D_00484A48->f90 = 1;
        if (D_00484A48->f70 != 0) {
            StateMachineSetState_28ede0(w, 0x88F4, 0);
        } else {
            StateMachineSetState_28ede0(w, 0x88D6, 0);
        }
        UiFadeWidgetAlpha_290690(v, 0x41, 0.0f, -0.125f, -1.0f);
    } else {
        factory_FactoryPartsPlaceWait_4f01a0(D_00484A4C);
    }
    return 1;
}
