#include "types.h"

struct T39E2C0 { u8 pad000[0x12]; s16 f12; };

extern const u8 D_004E96B0[];
extern void UiSetWidgetPos_290f60(const u8 *a, s32 b, s32 c, s32 d);

s32 CompleteCheckCursorPlace_39e2c0(struct T39E2C0 *p)
{
    UiSetWidgetPos_290f60(D_004E96B0, 5, 0, p->f12 * 27);
    return 1;
}
