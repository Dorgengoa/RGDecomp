#include "types.h"

struct S2910A0 { u8 pad000[0x14]; f32 f14; f32 f18; };

extern struct S2910A0 *UiFindWidget_290460(void *a, void *b);

void UiGetWidgetPos_2910a0(void *a, void *b, s32 *out1, s32 *out2)
{
    struct S2910A0 *q;

    *out2 = 0;
    *out1 = 0;
    q = UiFindWidget_290460(a, b);
    if (q != 0) {
        *out1 = (s32)q->f14;
        *out2 = (s32)q->f18;
    }
}
