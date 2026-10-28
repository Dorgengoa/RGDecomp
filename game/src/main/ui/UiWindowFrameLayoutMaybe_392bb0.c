/* rgp:protos */
#define RGP_SELF_UiWindowFrameLayoutMaybe_392bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct { f32 v[3]; } V3;
extern V3 D_0047FE20 __attribute__((section(".sdata")));
extern V3 D_0047FE30 __attribute__((section(".sdata")));
extern V3 D_0047FE40 __attribute__((section(".sdata")));
extern V3 D_0047FE50 __attribute__((section(".sdata")));
extern s16 D_00464118[16];
extern s16 D_00464120[16];
extern s16 D_00464128[16];
extern s16 D_00464130[16];

void UiWindowFrameLayoutMaybe_392bb0(s32 arg0, s8 *arg1, s32 x, s32 y, s32 mode) {
    s16 *p;
    s16 *q;
    s32 i;
    s32 div;
    s32 m;
    s32 d;
    f32 fx16;
    f32 fy16;
    f32 fx32;
    f32 fy32;

    if (arg1 == NULL) return;
    p = *(s16 **)(arg1 + 0x20);
    if (p == NULL) return;
    p[1] = 4;
    p[0] = 4;
    switch (mode) {
    case 0:
        break;
    case 1:
        p[2] = x - 8;
        p[3] = y - 8;
        p[7] = 4;
        p[6] = 4;
        p[4] = 0x34;
        p[5] = 0x8C;
        break;
    case 2:
        p[2] = x - 4;
        p[3] = y - 4;
        p[6] = 2;
        p[7] = 0x18;
        p[4] = 0xFC;
        p[5] = 0x24;
        break;
    case 3:
        p[2] = x - 4;
        p[3] = y - 4;
        p[6] = 2;
        p[7] = 0x18;
        p[4] = 0xF8;
        p[5] = 0x24;
        break;
    case 4:
        p[2] = x - 4;
        p[3] = y - 4;
        p[6] = 2;
        p[7] = 0x18;
        p[4] = 0xF4;
        p[5] = 0x24;
        break;
    }
    q = p + 0x10;
    div = 3;
    for (i = 0; i < 9; i++) {
        V3 a __attribute__((aligned(16)));
        V3 b __attribute__((aligned(16)));
        V3 c __attribute__((aligned(16)));
        V3 e __attribute__((aligned(16)));
        m = i % 3;
        d = i / 3;
        a = *(V3 *)(void *)&D_0047FE20;
        b = *(V3 *)(void *)&D_0047FE30;
        c = *(V3 *)(void *)&D_0047FE40;
        e = *(V3 *)(void *)&D_0047FE50;
        a.v[2] = x - 16;
        b.v[2] = y - 16;
        c.v[1] = x - 32;
        e.v[1] = y - 32;
        if (m != 1 || d != 1) {
            q[0] = a.v[m];
            q[1] = b.v[d];
            q[2] = c.v[m];
            q[3] = e.v[d];
            q[6] = D_00464128[m];
            q[7] = D_00464130[d];
            q[4] = D_00464118[m];
            q[5] = D_00464120[d];
        }
        q += 0x10;
    }
}
