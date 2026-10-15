#include "types.h"

extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32);

s32 UiMoveOrPlaceWidget_2a4af0(s32 *p, f32 v, s32 a, s32 b, s32 c)
{
    f32 z;

    z = 0.0f;
    if (v != z) {
        UiMoveWidgetUniform_290f50(*p, a, b, c, 1);
    } else {
        UiSetWidgetPos_290f60(*p);
    }
    return 1;
}
