#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

extern f32 D_0047FB50[4] __attribute__((section(".sdata")));
extern void GsDrawSpriteAnchorBL_383860(void *a, void *b, Vec4 *v, f32 c, f32 d, f32 e, f32 g);

void GsDrawSpriteAnchorBLAlpha_383810(void *a, void *b, f32 c, f32 d, f32 e, f32 g, f32 h)
{
    Vec4 v = *(const Vec4 *)D_0047FB50;

    v.w = 128.0f * h;
    GsDrawSpriteAnchorBL_383860(a, b, &v, c, d, e, g);
}
