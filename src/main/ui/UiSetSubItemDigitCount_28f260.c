#include "types.h"

struct R28F260 { u8 pad000[0x10]; s16 f10; };

extern struct R28F260 *UiGetWidgetSubItem_28f2b0(void *a, void *b, void *d);

void UiSetSubItemDigitCount_28f260(void *a, void *b, s32 v, void *d)
{
    struct R28F260 *r;
    s32 w;

    r = UiGetWidgetSubItem_28f2b0(a, b, d);
    if (r == 0) return;
    if ((s16)v > 0) {
        r->f10 = (s16)(v & 0xFFFF);
    }
}
