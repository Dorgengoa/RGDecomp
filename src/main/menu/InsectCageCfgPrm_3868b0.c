#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct E3868b0 {
    u8  f00;
    u8  pad01[3];
    f32 f04;
    f32 f08;
    f32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8  pad20[52 - 0x20];
} E3868b0;

extern s8 D_00483400;
extern E3868b0 *D_004832B0;

extern s32 VariantGetInt_15f780(Cur8 *);
extern f32 VariantGetFloat_15f740(Cur8 *);

s32 InsectCageCfgPrm_3868b0(Cur8 *q)
{
    E3868b0 *e;
    f32 v;
    f32 w;

    VariantGetInt_15f780(q++);
    e = &D_004832B0[D_00483400];
    e->f00 = VariantGetInt_15f780(q++);
    e->f04 = VariantGetFloat_15f740(q++);
    e->f08 = VariantGetFloat_15f740(q++);
    e->f0C = VariantGetFloat_15f740(q++);
    v = VariantGetFloat_15f740(q++);
    w = VariantGetFloat_15f740(q++);
    e->f10 = (s32)(60.0f * v);
    e->f14 = (s32)(60.0f * w);
    e->f18 = VariantGetInt_15f780(q++);
    e->f1C = VariantGetInt_15f780(q);
    D_00483400 = D_00483400 + 1;
    return 0;
}
