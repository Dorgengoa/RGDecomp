/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_342490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern f32 D_00482D08;
extern s16 D_00482D0C;
extern f32 D_0047D2CC;

s32 MenuGridCursorBobCb_342490(void *rgp_a0) {
    s32 u;
    s32 w;
    MenuCursorBobUpdate_342e70((void *)rgp_a0, 0, 0, 0, 0);
    if (D_00482D08 > 1.0f || D_00482D08 < 0.5f) {
        D_00482D0C = -D_00482D0C;
    }
    D_00482D08 = D_00482D08 + D_0047D2CC * (f32)D_00482D0C;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x198, D_00482D08);
    return 1;
}
