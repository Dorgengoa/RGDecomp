#include "types.h"

struct SFUN_0029caf0 { u8 pad000[0x4C4]; void *fh; };

extern s32 UiFindWidget_290460(void *a);
extern f32 UiGetWidgetAlpha_290770(void *a, s32 b);
extern void UiSetWidgetVisible_290010(void *a, s32 b, s32 c, s32 d);

s32 UiHideWidgetIfFaded_29caf0(struct SFUN_0029caf0 *p, s32 q)
{
    if (UiFindWidget_290460(p->fh) == 0) {
        return -1;
    }
    if (UiGetWidgetAlpha_290770(p->fh, q) <= 0.0f) {
        UiSetWidgetVisible_290010(p->fh, q, 0, -1);
        return 1;
    }
    return 0;
}
