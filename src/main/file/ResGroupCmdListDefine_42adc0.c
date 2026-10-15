#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern s32 VariantGetInt_15f780(SArg *);
extern s32 ResGroupListAppendNew_42c1a0(s32, s32, s32);

extern s32 D_00483FE0;
extern s32 D_00483FF4;
extern s16 D_0048400C;

s32 ResGroupCmdListDefine_42adc0(SArg *p0)
{
    s32 r1;
    s32 r2;
    s32 t0;

    D_0048400C = -1;
    D_00483FF4 = 0;
    r1 = VariantGetInt_15f780(p0++);
    r2 = VariantGetInt_15f780(p0);
    t0 = D_00483FE0;
    D_00483FF4 = ResGroupListAppendNew_42c1a0(t0, r1, r2);
    D_0048400C = 0;
    return 1;
}
