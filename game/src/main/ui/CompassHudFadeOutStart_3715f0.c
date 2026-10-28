/* rgp:protos */
#define RGP_SELF_CompassHudFadeOutStart_3715f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O_003715f0 {
    u8 pad000[0x18];
    f32 f18;
} O_003715f0;

void CompassHudFadeOutStart_3715f0(O_003715f0 *o, s32 n)
{
    if (n > 0) {
        goto div;
    }
    o->f18 = -1.0f;
    return;
div:
    o->f18 = -1.0f / (f32)n;
}
