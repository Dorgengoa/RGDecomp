/* rgp:protos */
#define RGP_SELF_InsectVsTeamListTitleCenter_37aa20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 func_4F3320(void);

extern s32 D_004831D4;

void InsectVsTeamListTitleCenter_37aa20(void) {
    s32 temp_16;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_3;

    temp_2 = func_4F3320();
    temp_16 = D_004831D4;
    if (temp_2 != 0 && temp_16 != 0) {
        UiSetTextString_28f510(temp_16, 0x9CAA, MsgTableLookup_28aa30(temp_2, 0x3ED), 0);
        temp_2_2 = UiGetWidgetTextWidth_28f400(temp_16, 0x9CAA, 0);
        var_3 = temp_2_2 >> 1;
        if (temp_2_2 < 0) {
            var_3 = (temp_2_2 + 1) >> 1;
        }
        UiSetTextX_28f590(temp_16, 0x9CAA, 0x100 - var_3, 0);
    }
}
