/* rgp:protos */
#define RGP_SELF_InsectCageMenuSlotTextSetStateMaybe_38d550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_00463E40[8];
extern s32 D_00463E48[8];
extern s32 D_00483308;

int InsectCageMenuSlotTextSetStateMaybe_38d550(s32 arg0, s32 arg1) { int rgp_v0 = 0;
    f32 f;
    s32 v;
    s32 i;

    f = D_00463E40[arg1];
    UiSetWidgetColor_2905b0(D_00483308, (u16)(arg0 + 0x7580), f, f, f, 1.0f);
    v = D_00463E48[arg1];
    for (i = 0; i < 5; i++) {
        (rgp_v0 = UiSetTextColor_290a40(D_00483308, (u16)(arg0 + 0x7580), v, i));
    }
return rgp_v0; }
