/* rgp:protos */
#define RGP_SELF_MenuWidgetFadeInOut_29fb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

typedef struct Obj {
    u8 pad[0x4C4];
    s32 f4C4;
} Obj;

s32 MenuWidgetFadeInOut_29fb00(Obj *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    f32 f21;
    f32 f20;
    f32 t0;

    f20 = 1.0f;
    f21 = 0.0f;
    t0 = UiGetWidgetAlpha_290770(arg0->f4C4, arg1);
    if (arg2 != 0) {
        if (arg3 != 0) {
            f21 = t0;
        }
        UiFadeWidgetAlpha_290690(arg0->f4C4, arg1, 1.0f, 0.125f, f21);
    } else {
        if (arg3 != 0) {
            f20 = t0;
        }
        UiFadeWidgetAlpha_290690(arg0->f4C4, arg1, 0.0f, 0.125f, f20);
    }
    return 1;
}
