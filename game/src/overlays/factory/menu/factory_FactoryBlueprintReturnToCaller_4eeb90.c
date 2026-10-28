/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintReturnToCaller_4eeb90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx {
    u8    pad00[0x80];
    void *f80;
    u8    pad84[0x4];
    void *f88;
    u8    pad8C[0x4];
    u8    f90;
} Ctx;

typedef struct Msg {
    s32 f0;
} Msg;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintReturnToCaller_4eeb90(void)
{
    Msg *m;
    s32  v;

    v = 0;
    switch (D_00484A48->f90) {
    case 0:
        v = -1;
        break;
    case 1:
        v = 1;
        break;
    case 2:
        v = 2;
        break;
    case 3:
        v = 3;
        break;
    case 4:
        v = 4;
        break;
    }
    if (v > 0) {
        UiSetWidgetVisible_290010(D_00484A48->f80, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(v);
        factory_FactoryMenuCaptionSlideIn_4eb220();
    }
    m = ((Msg *)FactoryGetRequestPtr_367ec0());
    switch (v) {
    case -1:
        StateMachineSetState_28ede0(D_00484A48->f88, 0x88CC, 0);
        break;
    case 1:
        StateMachineSetState_28ede0(D_00484A48->f88, 0x8926, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x41, 1.0f, 0.125f, -1.0f);
        m->f0 = 5;
        break;
    case 2:
        StateMachineSetState_28ede0(D_00484A48->f88, 0x8944, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x4D, 1.0f, 0.125f, -1.0f);
        m->f0 = 6;
        break;
    case 3:
        StateMachineSetState_28ede0(D_00484A48->f88, 0x8962, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x53, 1.0f, 0.125f, -1.0f);
        m->f0 = 7;
        break;
    case 4:
        StateMachineSetState_28ede0(D_00484A48->f88, 0x8980, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0xB0, 1.0f, 0.125f, -1.0f);
        m->f0 = 0;
        break;
    }
}
