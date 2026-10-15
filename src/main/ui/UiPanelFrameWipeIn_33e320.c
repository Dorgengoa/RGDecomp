#include "types.h"

s32 DrawEnvGetWidth_1451e0(s32);
s32 GetDrawCtx_15de80();
u8 *UiFindWidget_290460(s32, s32);
void UiPanelGetGlyphSpacing_33dfc0(s32);
s32 UiPanelGetWidgetList_33e860();
s32 UiPanelGetCellSize_33e920(s32, s32 *, s32 *);

s32 UiPanelFrameWipeIn_33e320(s32 arg0, f32 fparg0) {
    s32 sp4C;
    s32 sp48;
    f32 f;
    s32 lim;
    s32 cur;
    f32 fl;
    s32 v;
    u8 *p;
    u8 *t;

    t = UiFindWidget_290460(UiPanelGetWidgetList_33e860(), 2);
    if (t == 0) {
        return 0;
    }
    p = *(u8 **)(t + 0x20);
    if (p == 0) {
        return 0;
    }
    UiPanelGetGlyphSpacing_33dfc0(arg0);
    UiPanelGetCellSize_33e920(arg0, &sp4C, &sp48);
    v = GetDrawCtx_15de80();
    if (v == 0) {
        return 0;
    }
    lim = DrawEnvGetWidth_1451e0(v);
    lim += 0xC0;
    f = (f32)*(s16 *)(p + 4) + fparg0;
    if (f >= (f32)lim) {
        *(s16 *)(p + 4) = lim;
        return 1;
    }
    *(s16 *)(p + 4) = (s32)f;
    return 0;
}
