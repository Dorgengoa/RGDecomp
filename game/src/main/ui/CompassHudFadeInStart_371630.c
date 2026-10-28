/* rgp:protos */
#define RGP_SELF_CompassHudFadeInStart_371630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O_00371630 {
    u8 pad000[0x18];
    f32 f18;
} O_00371630;

void CompassHudFadeInStart_371630(O_00371630 *o, s32 n)
{
    if (n > 0) {
        goto div;
    }
    o->f18 = 1.0f;
    return;
div:
    o->f18 = 1.0f / (f32)n;
}
