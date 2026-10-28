/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialChoiceClose_4edac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Head {
    u8    pad00[0x6];
    s16   f06;
    u8    pad08[0x38];
    void *f40;
    void *f44;
    void *f48;
} Head;

typedef struct Rec {
    u8  pad00[0x12];
    s16 f12;
} Rec;

extern Head *D_00484A58;                        /* _gp - 0x718 */
extern f32   D_0047D50C;                        /* _gp - 0x7C64 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialChoiceClose_4edac0(void)
{
    void *h;
    f32  *p;

    h = D_00484A58->f40;
    if (h == 0) {
        return 0;
    }
    p = ((f32 *)UiGetWidgetColor_2904b0(h, (u16)(((Rec *)UiEntryListGetCurrentData_28ec60(D_00484A58->f44))->f12 + 0x72)));
    factory_FactoryMaterialFrameScroll_4f3a40(D_00484A58);
    if (*p <= 1.0f) {
        if (UiGetWidgetAlpha_290770(h, 0x6D) >= 1.0f) {
            UiFadeWidgetAlpha_290690(h, 0x6D, 0.0f, D_0047D50C, -1.0f);
            UiFadeWidgetAlpha_290690(h, 0x64, 0.0f, D_0047D50C, -1.0f);
            UiFadeWidgetAlpha_290690(h, 0x67, 0.0f, D_0047D50C, -1.0f);
        }
    }
    if (UiGetWidgetAlpha_290770(h, 0x6D) <= 0.0f) {
        if (D_00484A58->f06 >= 0) {
            StateMachineSetState_28ede0(D_00484A58->f48, 0x89A8, 0);
        } else {
            StateMachineSetState_28ede0(D_00484A58->f48, 0x8980, 0);
        }
    }
    return 1;
}
