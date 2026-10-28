/* rgp:protos */
#define RGP_SELF_GsDrawSpriteCenteredAlpha_383480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

extern f32 D_0047FB70[4] __attribute__((section(".sdata")));
/*rgp*/

void GsDrawSpriteCenteredAlpha_383480(void *a, void *b, f32 c, f32 d, f32 e, f32 g, f32 h)
{
    Vec4 v __attribute__((aligned(16))) = *(const Vec4 *)D_0047FB70;

    v.w = 128.0f * h;
    GsDrawSpriteCentered_3834d0(a, b, &v, c, d, e, g);
}
