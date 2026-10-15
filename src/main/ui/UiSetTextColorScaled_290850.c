#pragma peephole off
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    u32 col;
} Obj;

extern Obj *UiGetWidgetText_28f620(s32, s32, s32);

static inline u8 sc(u32 c, f32 f) {
    return (u8)((f32)c * f);
}

static inline u8 ch(u32 c) {
    return c;
}

s32 UiSetTextColorScaled_290850(s32 arg0, s32 arg1, u32 col, s32 arg3, f32 f)
{
    Obj *o;
    u8 g;
    u8 b;
    u8 r;
    s32 a;

    o = UiGetWidgetText_28f620(arg0, arg1, arg3);
    if (o == 0) {
        return 0;
    }
    g = sc((col & 0xFF00) >> 8, f);
    b = sc(col & 0xFF, f);
    r = sc((col & 0xFF0000) >> 16, f);
    a = (col & 0xFF000000) >> 24;
    o->col = ((a & 0xFF) << 24) | ((r << 16) | (b | (g << 8)));
    return 1;
}
