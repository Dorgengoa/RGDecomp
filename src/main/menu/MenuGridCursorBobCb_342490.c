#include "types.h"

extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void MenuCursorBobUpdate_342e70(s32, s32, s32, s32, s32);
extern s32 D_00482360;
extern f32 D_00482D08;
extern s16 D_00482D0C;
extern f32 D_0047D2CC;

s32 MenuGridCursorBobCb_342490(void) {
    s32 u;
    s32 w;
    MenuCursorBobUpdate_342e70(u, w, 0, 0, 0);
    if (D_00482D08 > 1.0f || D_00482D08 < 0.5f) {
        D_00482D0C = -D_00482D0C;
    }
    D_00482D08 = D_00482D08 + D_0047D2CC * (f32)D_00482D0C;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x198, D_00482D08);
    return 1;
}
