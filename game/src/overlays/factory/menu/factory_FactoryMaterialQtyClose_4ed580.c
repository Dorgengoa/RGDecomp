/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialQtyClose_4ed580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Head {
    u8    pad00[0x8];
    s16   f08;
    u8    pad0A[0x36];
    void *f40;
    void *f44;
    void *f48;
    u8    pad4C[0x2C];
    u8    f78;
} Head;

extern Head *D_00484A58;                        /* _gp - 0x718 */
extern f32   D_0047D4FC;                        /* _gp - 0x7C74 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialQtyClose_4ed580(void)
{
    void *h;

    h = D_00484A58->f40;
    if (h == 0) {
        return 0;
    }
    UiEntryListGetCurrentData_28ec60(D_00484A58->f44);
    factory_FactoryMaterialFrameScroll_4f3a40(D_00484A58);
    if (*((f32 *)UiGetWidgetColor_2904b0(h, 0x79)) <= 1.0f) {
        if (UiGetWidgetAlpha_290770(h, 0x77) >= 1.0f) {
            UiFadeWidgetAlpha_290690(h, 0x77, 0.0f, D_0047D4FC, -1.0f);
        }
    }
    if (UiGetWidgetAlpha_290770(h, 0x77) <= 0.0f) {
        if (D_00484A58->f08 > 0) {
            D_00484A58->f78 = 1;
            StateMachineSetState_28ede0(D_00484A58->f48, 0x8980, 0);
            UiEntryListSelectByTag_28ea90(D_00484A58->f44, 0x894E, 0);
            UiSetWidgetAlpha_2907a0(D_00484A58->f40, 0xB0, 0.0f);
            UiSetWidgetAlpha_2907a0(D_00484A58->f40, 0x69, 1.0f);
        } else {
            StateMachineSetState_28ede0(D_00484A58->f48, 0x8980, 0);
        }
    }
    return 1;
}
