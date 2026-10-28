/* rg-override: replaces game/src/main/gfx/GsDrawSpriteCentered_3834d0.c sha256 628d61ef0d7411bc8c6855ea6de60528d1c2ba359c4a7f43569cc5cd71d48ffb
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_GsDrawSpriteCentered_3834d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);

extern f32 D_0047D7E4;
/*rgp*/
/*rgp*/

void GsDrawSpriteCentered_3834d0(void *o, s32 *r, void *c, f32 x, f32 y, f32 w, f32 h)
{
    f32 k;

    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        k = rg_hud_xscale();
    } else {
        k = 1.0f;
    }
    w = w * (0.5f * k);
    h = h * D_0047D7E4;
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
            a[2] = x + w;
            a[3] = y + h;
            GsDrawSpriteClipped_3839d0(o, a, b, c);
        }
    }
}
