/* rgp:protos */
#define RGP_SELF_UiPageScrollBarLayout_289710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s32 f10;
    f32 f14;
    s32 pad[2];
} R289;

typedef struct { s16 v[3]; } S3;
typedef struct { f32 v[3]; } V3;
typedef union { s16 v[3]; S3 s; } AU;
/*rgp*/
extern s16 D_0047EA48;
extern s16 D_0047EA4A;
extern s16 D_0047EA4C;
extern s16 D_0047EA50;
extern s16 D_0047EA52;
extern s16 D_0047EA54;
extern f32 D_0047EA58;
extern f32 D_0047EA5C;
extern f32 D_0047EA60;

f32 UiPageScrollBarLayout_289710(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s16 w[3];
    AU au __attribute__((aligned(16)));
    f32 f[3];
    R289 *base;
    R289 *rec;
    s32 n;
    s32 j;
    f32 res;
    f32 fa;

    base = ((R289 *)UiPageGetWidgetSprites_289ad0(arg0, arg1));
    if (base == 0) {
        return 0.0f;
    }
    fa = arg2;
    *(S3 *)w = *(S3 *)&D_0047EA48;
    au.s = *(S3 *)&D_0047EA50;
    *(V3 *)f = *(V3 *)&D_0047EA58;
    {
    f32 v[3] = {0};
    n = arg4 - arg3;
    if (n < 0) {
        n = 0;
    }
    if (n == 0) {
        for (j = 0; j < 3; j++) {
            rec = &base[j];
            rec->f0 = 0;
            rec->fC = 8;
            rec->f4 = 8;
            rec->fE = au.v[j];
            rec->f6 = au.v[j];
            rec->f14 = 0.0f;
            rec->f10 = 0;
        }
        base[1].f6 = arg2 - (au.v[0] + au.v[2]);
        base[0].f2 = 0;
        base[1].f2 = au.v[0];
        base[2].f2 = au.v[0] + base[1].f6;
        return 0.0f;
    }
    f[1] = (f32)((arg2 - (au.v[0] + au.v[2])) / au.v[1] - (n + 2));
    if (f[1] < 1.0f) {
        f[1] = 1.0f;
    }
    v[0] = 0.0f;
    v[1] = v[0] + (f32)au.v[0];
    v[2] = v[1] + (f32)au.v[1] * f[1];
    res = (fa - (v[2] + (f32)au.v[2])) / (f32)n;
    rec = base;
    for (j = 0; j < 3; j++) {
        rec->f0 = 0;
        rec->f2 = (s32)v[j];
        if (arg5 != 0) {
            rec->fC = 0;
            rec->f4 = 0;
            rec->fE = 0;
            rec->f6 = 0;
        } else {
            rec->fC = 8;
            rec->f4 = 8;
            rec->fE = au.v[j];
            rec->f6 = au.v[j];
        }
        rec->f8 = 0x5E;
        rec->fA = w[j];
        rec->f10 = 0;
        rec->f14 = f[j];
        rec++;
    }
    *(f32 *)(arg0 + 0x58) = res;
    return res;
    }
}
