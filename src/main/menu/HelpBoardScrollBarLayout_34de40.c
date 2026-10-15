


#pragma divbyzerocheck on

#include "types.h"

typedef struct V3  { f32 x; f32 y; f32 z; } V3;
typedef struct S3  { s16 x; s16 y; s16 z; } S3;
typedef union  AU  { s16 v[3]; S3 s; } AU;
typedef struct Row { s16 ax; s16 ay; s16 aw; s16 ah;
                     s16 bx; s16 by; s16 bw; s16 bh;
                     f32 f10; f32 f14; u8 pad18[8]; } Row;

typedef struct W {u8 pad[0x20];Row *r;} W;
extern Row *UiGetWidgetSprite_28fe10(void *,s32,s32);
extern void *D_00482360;
extern f32   D_00482E88;
extern s16   D_0047F6F8[3];
extern s16   D_0047F700[3];
extern f32   D_0047F708;

f32 HelpBoardScrollBarLayout_34de40(s32 h, s32 lo, s32 hi)
{
    s16  b[3];
    AU   au;
    f32  c[3];
    Row *r;
    s32  i;
    s32  t;
    s32  q;
    f32  ret;
    f32  hf;

    hf = (f32)h;
    *(S3 *)b = *(S3 *)&D_0047F6F8;
    au.s = *(S3 *)&D_0047F700;
    *(V3 *)c = *(V3 *)&D_0047F708;
    {
    f32  d[3] = {0};

    r=UiGetWidgetSprite_28fe10(D_00482360,0x21B,0);
    if (r == 0) {
        return 0.0f;
    }

    t = hi - lo;
    if (t < 0) {
        t = 0;
    }

    if (t == 0) {
        for (i = 0; i < 3; i++) {
            r[i].ax = 0x178;
            r[i].bw = 8;
            r[i].aw = 8;
            r[i].bh = au.v[i];
            r[i].ah = au.v[i];
            r[i].f14 = 0.0f;
            r[i].f10 = 0.0f;
        }
        r[1].ah = h - (au.v[0] + au.v[2]);
        ret = 0.0f;
        r[0].ay = 0x3E;
        r[1].ay = 0x3E + au.v[0];
        r[2].ay = r[1].ay + r[1].ah;
    } else {
        q = (h - (au.v[0] + au.v[2])) / au.v[1] - (t + 2);
        c[1] = (f32)q;
        if (c[1] < 1.0f) {
            c[1] = 1.0f;
        }
        d[0] = 0.0f;
        d[1] = d[0] + (f32)au.v[0];
        d[2] = d[1] + (f32)au.v[1] * c[1];
        ret = (hf - (d[2] + (f32)au.v[2])) / (f32)t;
        for (i = 0; i < 3; i++) {
            r->ax = 0x178;
            r->ay = (s32)(62.0f + d[i]);

                r->bw = 8;
                r->aw = 8;
                r->bh = au.v[i];
                r->ah = au.v[i];

            r->bx = 0x5E;
            r->by = b[i];
            r->f10 = 0.0f;
            r->f14 = c[i];
            r++;
        }
        D_00482E88 = ret;
    }
    return ret;
    }
}
