/* rgp:protos */
#define RGP_SELF_MapWarpRequest_285d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct G285d80 {
    u8  f00;
    u8  pad01;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 a[2];
    f32 b[2];
    f32 c[3];
    f32 d[3];
} G285d80;

extern G285d80 D_004D7E00;
/*rgp*/

int MapWarpRequest_285d80(s16 id, f32 x, f32 y, f32 z, f32 w, f32 *p, f32 *q)
{
    s32 i;

    D_004D7E00.f04 = -1;
    D_004D7E00.f06 = -1;
    D_004D7E00.f08 = -1;
    D_004D7E00.f0A = -1;
    for (i = 0; i < 2; i++) {
        D_004D7E00.a[i] = 0.0f;
        D_004D7E00.b[i] = 0.0f;
    }
    for (i = 0; i < 3; i++) {
        D_004D7E00.c[i] = 0.0f;
        D_004D7E00.d[i] = 0.0f;
    }
    D_004D7E00.f00 = 1;
    D_004D7E00.f02 = id;
    D_004D7E00.f0C = x;
    D_004D7E00.f10 = y;
    D_004D7E00.f14 = z;
    D_004D7E00.f18 = w;
    D_004D7E00.a[0] = 20.0f;
    D_004D7E00.a[1] = -20.0f;
    D_004D7E00.b[0] = -20.0f;
    D_004D7E00.b[1] = -20.0f;
    for (i = 0; i < 3; i++) {
        D_004D7E00.c[i] = p[i];
        D_004D7E00.d[i] = q[i];
    }
    return GameReqQueuePushBack_1f5b50(5, -1);
}
