#include "types.h"

struct S290D30 { u8 pad000[0x14]; f32 f14; f32 f18; u8 pad01C[0x44]; f32 f60; f32 f64; };

extern struct S290D30 *UiFindWidget_290460(void *a, void *b);

s32 UiWidgetIsMoving_290d30(void *a, void *b)
{
    struct S290D30 *q;

    q = UiFindWidget_290460(a, b);
    if (q == 0) return 0;
    if (q->f14 != q->f60) goto one;
    if (q->f18 != q->f64) goto one;
    return 0;
one:
    return 1;
}
