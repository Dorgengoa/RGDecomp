#include "types.h"

struct T2A10F0 { void *f00; };

extern "C" f32 D_0047D288;
extern "C" f32 *UiGetWidgetColor_2904b0(void *a, u16 k);

extern "C" u8 MenuWidgetIsDimmed_2a10f0(struct T2A10F0 *p, u16 a, s16 b)
{
    f32 *r;
    s32 ok;

    r = UiGetWidgetColor_2904b0(p->f00, (u16)(a + b));
    ok = D_0047D288 == *r;
    return ok;
}
