#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct G16f770 {
    u8  pad00[0x0C];
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
} G16f770;

extern G16f770 *D_00481198;
extern f32 VariantGetFloat_15f740(Cur8 *);

s32 AmixerCfgClipDataCmd_16f770(Cur8 *q, s32 mode)
{
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    G16f770 *g;

    if (D_00481198 == 0) {
        return 0;
    }
    a = VariantGetFloat_15f740(q++);
    b = VariantGetFloat_15f740(q++);
    c = VariantGetFloat_15f740(q++);
    d = 1.0f;
    e = 1.0f;
    f = 1.0f;
    if (mode >= 4) {
        d = VariantGetFloat_15f740(q++);
    }
    if (mode >= 5) {
        e = 1.0f + VariantGetFloat_15f740(q++);
    }
    if (mode >= 6) {
        f = VariantGetFloat_15f740(q);
    }
    g = D_00481198;
    g->f0C = a;
    g->f10 = b;
    g = D_00481198;
    g->f14 = c;
    g->f18 = d;
    g->f20 = e;
    g = D_00481198;
    g->f1C = f;
    return 1;
}
