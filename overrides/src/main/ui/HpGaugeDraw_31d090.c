/* rg-override: replaces game/src/main/ui/HpGaugeDraw_31d090.c sha256 2c22fb18a4cb53fd9d7ac89dcee70f366b689bca6e8a85c07a2e2181b50b9b2e
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_HpGaugeDraw_31d090 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);
extern float rg_hud_xscale_world(void); /* stage 2: world-anchored (TaskDrawStatus, layout suppressed) */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 HpGaugeDraw_31d090(void *p)
{
    f32 s;
    s32 m;

    s = 1.0f;
    m = ((signed char)HpGaugeGetMode_31d3c0(p));
    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        s = s * rg_hud_xscale_world();
    }
    switch (m) {
    case 0:
        HpGaugeReset_31e1e0(p);
        break;
    case 1:
        HpGaugeSetBarWidth_31e300(p, (s16)(40.0f * s));
        HpGaugeDrawAll_31ce00(p);
        break;
    case 2:
        break;
    }
    return m;
}
