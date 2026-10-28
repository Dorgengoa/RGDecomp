/* rgp:protos */
#define RGP_SELF_FadeSnap_186d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 x0; u8 pad[0x14]; f32 f18; } S;

#pragma opt_propagation off
void FadeSnap_186d80(S *o, s32 list)
{
    s32 z;
    if (list == 0) {
        o->f18 = 0.0f;
        return;
    }
    z = o->x0 == 0;
    if (z) o->f18 = 1.0f; else o->f18 = 0.0f;
    o->f18 = -1.0f;
}
