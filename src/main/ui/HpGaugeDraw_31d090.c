#include "types.h"

extern s32 HpGaugeGetMode_31d3c0(void *p);
extern s32 IsWidescreen_1c6ab0(void);
extern void HpGaugeReset_31e1e0(void *p);
extern void HpGaugeSetBarWidth_31e300(void *p, s16 v);
extern void HpGaugeDrawAll_31ce00(void *p);

s32 HpGaugeDraw_31d090(void *p)
{
    f32 s;
    s32 m;

    s = 1.0f;
    m = HpGaugeGetMode_31d3c0(p);
    if (IsWidescreen_1c6ab0() != 0) {
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
