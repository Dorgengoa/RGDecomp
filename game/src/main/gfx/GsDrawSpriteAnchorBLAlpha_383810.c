/* rgp:protos */
#define RGP_SELF_GsDrawSpriteAnchorBLAlpha_383810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

extern f32 D_0047FB50[4] __attribute__((section(".sdata")));
/*rgp*/

void GsDrawSpriteAnchorBLAlpha_383810(void *a, void *b, f32 c, f32 d, f32 e, f32 g, f32 h)
{
    Vec4 v __attribute__((aligned(16))) = *(const Vec4 *)D_0047FB50;

    v.w = 128.0f * h;
    GsDrawSpriteAnchorBL_383860(a, b, &v, c, d, e, g);
}
