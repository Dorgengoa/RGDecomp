/* rgp:protos */
#define RGP_SELF_LensFlareSetupElements_2ee040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R2EE040 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    f32 e;
    f32 f;
} R2EE040;

extern f32 D_0047D288 __attribute__((section(".sdata")));
extern f32 D_0047D354 __attribute__((section(".sdata")));
extern f32 D_0047D5D0 __attribute__((section(".sdata")));
extern f32 D_0047DB50 __attribute__((section(".sdata")));
extern f32 D_0047DCCC __attribute__((section(".sdata")));

void LensFlareSetupElements_2ee040(R2EE040 *p)
{
    p[0].b = 0;
    p[0].a = 0;
    p[0].c = 32;
    p[0].d = 32;
    p[0].f = 5.0f;
    p[0].e = 4.0f;
    p[1].b = 0;
    p[1].a = 32;
    p[1].c = 64;
    p[1].d = 32;
    p[1].f = D_0047DCCC;
    p[1].e = D_0047D354;
    p[2].b = 32;
    p[2].a = 0;
    p[2].c = 32;
    p[2].d = 64;
    p[2].f = 23.0f;
    p[2].e = 1.0f;
    p[3].b = 0;
    p[3].a = 64;
    p[3].c = 128;
    p[3].d = 64;
    p[3].f = 28.0f;
    p[3].e = D_0047DB50;
    p[4].b = 32;
    p[4].a = 0;
    p[4].c = 32;
    p[4].d = 64;
    p[4].f = 42.0f;
    p[4].e = D_0047D288;
    p[5].b = 0;
    p[5].a = 0;
    p[5].c = 32;
    p[5].d = 32;
    p[5].f = 60.0f;
    p[5].e = D_0047D5D0;
    p[6].b = 0;
    p[6].a = 0;
    p[6].c = 32;
    p[6].d = 32;
    p[6].f = 64.0f;
    p[6].e = D_0047D5D0;
    p[7].b = 0;
    p[7].a = 64;
    p[7].c = 128;
    p[7].d = 64;
    p[7].f = 75.0f;
    p[7].e = D_0047D5D0;
    p[8].b = 32;
    p[8].a = 0;
    p[8].c = 32;
    p[8].d = 64;
    p[8].f = 77.0f;
    p[8].e = D_0047DB50;
    p[9].b = 0;
    p[9].a = 32;
    p[9].c = 64;
    p[9].d = 32;
    p[9].f = 84.0f;
    p[9].e = D_0047D5D0;
    p[10].b = 64;
    p[10].a = 0;
    p[10].c = 64;
    p[10].d = 128;
    p[10].f = 90.0f;
    p[10].e = D_0047D354;
    p[11].b = 64;
    p[11].a = 64;
    p[11].c = 128;
    p[11].d = 128;
    p[11].f = 100.0f;
    p[11].e = 1.5f;
}
