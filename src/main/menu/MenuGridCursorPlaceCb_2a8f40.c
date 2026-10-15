#include "types.h"

struct T2A8F40 { u8 pad000[0x10]; s16 f10; s16 f12; };

extern void *D_00482360;
extern void UiSetWidgetPos_290f60(void *a, s32 b, s32 c, s32 d);

s32 MenuGridCursorPlaceCb_2a8f40(struct T2A8F40 *p)
{
    UiSetWidgetPos_290f60(D_00482360, 0xAE, p->f10 * 97 + 0x11, p->f12 * 97 + 0x31);
    return 1;
}
