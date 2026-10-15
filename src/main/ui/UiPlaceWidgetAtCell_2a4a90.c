#include "types.h"

struct T2A4A90 { u8 pad000[0x10]; s16 f10; s16 f12; s16 f14; s16 f16; };

extern void UiMoveOrPlaceWidget_2a4af0(void *a, void *b, s32 x, s32 y);

s32 UiPlaceWidgetAtCell_2a4a90(void *a, void *b, struct T2A4A90 *p)
{
    if (p == 0) return 0;
    UiMoveOrPlaceWidget_2a4af0(a, b, (p->f10 + p->f14) * 48, (p->f12 + p->f16) * 56);
    return 1;
}
