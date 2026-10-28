/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuGetFadeAlpha_511780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00511780 -- `mtc1 $0,$f0` on the else side is the 0.0f return. */

typedef struct Obj { u8 pad00[0x14]; u8 f14; } Obj;

/*rgp*/

f32 normal_SpaceMenuGetFadeAlpha_511780(Obj *p)
{
    if (p->f14 >= 2) {
        return UiGetWidgetAlpha_290770(p, 2);
    }
    return 0.0f;
}
