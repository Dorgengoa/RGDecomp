/* rgp:protos */
#define RGP_SELF_MenuPartyFadeSequenceStep_2b9240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D670;
extern f32 D_0047D674;
extern s32 D_00482360;
extern s32 D_00482370;
extern s16 D_00482568 __attribute__((section(".sdata")));
#define W (*(s16 *)&D_00482568)
#define R (*(volatile s16 *)&D_00482568)

s32 MenuPartyFadeSequenceStep_2b9240(s32 arg0, s32 arg1, s32 arg2)
{
    f32 f;
    s16 t;

    if (D_00482568 == 0) {
        UiFadeWidgetAlpha_290690(D_00482360, arg0, 0.0f, D_0047D670, -1.0f);
        W = 1;
    } else {
        f = UiGetWidgetAlpha_290770(D_00482360, arg0);
        if (f < D_0047D5D0 && R == 1) {
            UiFadeWidgetColor_2904e0(D_00482360, arg1, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5D0);
            W = 2;
        }
        if (R > 1) {
            f = UiGetWidgetAlpha_290770(D_00482360, arg1);
            if (!(f < D_0047D35C)) {
                UiFadeWidgetColor_2904e0(D_00482360, arg1, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D674);
            } else if (f <= 1.0f) {
                t = R + 1;
                W = t;
                if (t > 8) {
                    W = 0;
                    return 1;
                }
                if (t == 4) {
                    MenuWidgetFadeInOut_29fb00(D_00482370, arg2, 0, 0);
                }
            }
        }
    }
    return 0;
}
