/* rgp:protos */
#define RGP_SELF_EffectSetPosXyz_2e0ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;

extern f32 D_0047EEF0;
extern f32 D_0047EEF4;
extern f32 D_0047EEF8;
extern f32 D_0047EEFC;
/*rgp*/

void EffectSetPosXyz_2e0ad0(void *a, void *b, f32 x, f32 y, f32 z)
{
    Vec4 v __attribute__((aligned(16)));

    v.x = D_0047EEF0;
    v.y = D_0047EEF4;
    v.z = D_0047EEF8;
    v.w = D_0047EEFC;
    v.x = x;
    v.y = y;
    v.z = z;
    EffectSetPos_2e0bb0(a, b, &v);
}
