/* rgp:protos */
#define RGP_SELF_SceneSetTimeOfDay_1c5200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S1C5 {
    u8  pad000[0x4388];
    f32 f4388;
} S1C5;

void SceneSetTimeOfDay_1c5200(S1C5 *p, f32 v)
{
    v = v - 24.0f * (f32)(s32)(v / 24.0f);
    if (v < 0.0f) {
        v = v + 24.0f;
    }
    p->f4388 = v;
}
