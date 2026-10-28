/* rgp:protos */
#define RGP_SELF_EffectSetScaleXyz_2e0c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;

extern f32 D_0047EEE0;
extern f32 D_0047EEE4;
extern f32 D_0047EEE8;
extern f32 D_0047EEEC;
/*rgp*/

void EffectSetScaleXyz_2e0c90(void *a, void *b, f32 x, f32 y, f32 z)
{
    Vec4 v __attribute__((aligned(16)));

    v.x = D_0047EEE0;
    v.y = D_0047EEE4;
    v.z = D_0047EEE8;
    v.w = D_0047EEEC;
    v.x = x;
    v.y = y;
    v.z = z;
    EffectSetScale_2e0ce0(a, b, &v);
}
