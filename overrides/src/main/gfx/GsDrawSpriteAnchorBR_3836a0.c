/* rg-override: replaces game/src/main/gfx/GsDrawSpriteAnchorBR_3836a0.c sha256 fc3968fddc2ecaae5e723f1047736e2cdbfd9f4d4f913563065d6bb1648acf69
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_GsDrawSpriteAnchorBR_3836a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);

extern f32 D_0047D7EC;
/*rgp*/
/*rgp*/

void GsDrawSpriteAnchorBR_3836a0(void *o, s32 *r, void *c, f32 x, f32 y, f32 w, f32 h)
{
    f32 s;

    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        s = rg_hud_xscale();
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

            a[0] = x - w;
            a[1] = y - h;
            a[2] = x;
            a[3] = y;
            GsDrawSpriteClipped_3839d0(o, a, b, c);
        }
    }
}
