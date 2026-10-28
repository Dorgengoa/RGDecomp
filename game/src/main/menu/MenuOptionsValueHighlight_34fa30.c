/* rgp:protos */
#define RGP_SELF_MenuOptionsValueHighlight_34fa30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma tailcall off

struct H34fa30 { u16 a; u16 b; };

/*rgp*/

int MenuOptionsValueHighlight_34fa30(s32 a, s32 b, s32 c, u16 d, u16 e)
{
    struct H34fa30 t __attribute__((aligned(16)));
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
    return MenuOptionsChoiceHighlight_34fa80(x, y);
}
