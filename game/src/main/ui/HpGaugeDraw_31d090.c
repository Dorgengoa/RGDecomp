/* rgp:protos */
#define RGP_SELF_HpGaugeDraw_31d090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
        s = s * 0.75f;
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
