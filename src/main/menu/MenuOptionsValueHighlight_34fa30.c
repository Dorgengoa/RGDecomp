#include "types.h"
#pragma tailcall off

struct H34fa30 { u16 a; u16 b; };

extern void MenuOptionsChoiceHighlight_34fa80(u16, u16);

void MenuOptionsValueHighlight_34fa30(s32 a, s32 b, s32 c, u16 d, u16 e)
{
    struct H34fa30 t;
    u16 y;
    u16 x;

    x = t.a;
    y = t.b;
    if (a == b) {
        x = d;
        y = e;
    } else if (a == c) {
        x = e;
        y = d;
    }
    MenuOptionsChoiceHighlight_34fa80(x, y);
}
