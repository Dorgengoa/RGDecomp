/* rgp:protos */
#define RGP_SELF_GsDrawSpriteAnchorBL_383860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D7EC;
/*rgp*/
/*rgp*/

void GsDrawSpriteAnchorBL_383860(void *o, s32 *r, void *c, f32 x, f32 y, f32 w, f32 h)
{
    f32 s;

    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        s = 0.75f;
    } else {
        s = 1.0f;
    }
    w = w * s;
    h = h * D_0047D7EC;
    {
        f32 b[4] __attribute__((aligned(16))) = {0};

        b[0] = (f32)r[0];
        b[1] = (f32)r[1];
        b[2] = (f32)(r[0] + r[2]);
        b[3] = (f32)(r[1] + r[3]);
        {
            f32 a[4] __attribute__((aligned(16))) = {0};

            a[0] = x;
            a[1] = y - h;
            a[2] = x + w;
            a[3] = y;
            GsDrawSpriteClipped_3839d0(o, a, b, c);
        }
    }
}
