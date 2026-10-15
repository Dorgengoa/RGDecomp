#include "types.h"

extern f32 D_0047D7EC;
extern s32 IsWidescreen_1c6ab0(void *);
extern void GsDrawSpriteClipped_3839d0(void *, f32 *, f32 *, void *);

void GsDrawSpriteAnchorBL_383860(void *o, s32 *r, void *c, f32 x, f32 y, f32 w, f32 h)
{
    f32 s;

    if (IsWidescreen_1c6ab0(o) != 0) {
        s = 0.75f;
    } else {
        s = 1.0f;
    }
    w = w * s;
    h = h * D_0047D7EC;
    {
        f32 b[4] = {0};

        b[0] = (f32)r[0];
        b[1] = (f32)r[1];
        b[2] = (f32)(r[0] + r[2]);
        b[3] = (f32)(r[1] + r[3]);
        {
            f32 a[4] = {0};

            a[0] = x;
            a[1] = y - h;
            a[2] = x + w;
            a[3] = y;
            GsDrawSpriteClipped_3839d0(o, a, b, c);
        }
    }
}
