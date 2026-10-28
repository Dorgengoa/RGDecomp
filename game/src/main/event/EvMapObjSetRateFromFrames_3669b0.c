/* rgp:protos */
#define RGP_SELF_EvMapObjSetRateFromFrames_3669b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O_003669b0 {
    u8 pad000[0x318];
    f32 f318;
} O_003669b0;

void EvMapObjSetRateFromFrames_3669b0(O_003669b0 *o, s32 n)
{
    if (n > 0) {
        goto div;
    }
    o->f318 = 1.0f;
    return;
div:
    o->f318 = 1.0f / (f32)n;
}
