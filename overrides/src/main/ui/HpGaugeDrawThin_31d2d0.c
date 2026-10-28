/* rg-override: replaces game/src/main/ui/HpGaugeDrawThin_31d2d0.c sha256 4901759964836bff5e2ac54285531fdb7c3a0eaf531edf4e275252a497800011
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_HpGaugeDrawThin_31d2d0 1
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

s32 HpGaugeDrawThin_31d2d0(void *p)
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
        HpGaugeDrawAllThin_31dff0(p);
        break;
    case 2:
        break;
    }
    return m;
}
