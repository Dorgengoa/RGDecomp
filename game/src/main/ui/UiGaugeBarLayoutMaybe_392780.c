/* rgp:protos */
#define RGP_SELF_UiGaugeBarLayoutMaybe_392780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

extern s16 D_00464178[0x100];
extern s16 D_00464180[0x100];

typedef struct {
    s16 h0, h2, h4, h6, h8, hA, hC, hE;
    f32 f10, f14;
    s16 h18, h1A, h1C, h1E;
} S;

void UiGaugeBarLayoutMaybe_392780(s32 pd0, void *arg1, s32 arg2, f32 a, f32 b)
{
    S *p;
    f32 r;
    f32 w;
    s16 x;
    s16 y;

    if (arg1 == NULL) {
        return;
    }
    p = *(S **)((u8 *)arg1 + 0x20);
    if (!b || p == NULL) {
        return;
    }
    { f32 k = 60.0f; r = k * (a / b); }
    w = 64.0f;
    p[0].h0 = 0;
    p[0].h2 = 0;
    p[0].h4 = w;
    p[0].h6 = 8;
    p[0].h8 = 0x98;
    p[0].hA = 0x94;
    p[0].hC = 0x40;
    p[0].hE = 8;
    p[0].h18 = 0;
    p[0].h1A = 0;
    p[0].f10 = p[0].f14 = p[0].h1A;
    p[1].h0 = 2;
    p[1].h2 = 2;
    p[1].h4 = r;
    p[1].h6 = 4;
    x = D_00464178[arg2];
    y = D_00464180[arg2];
    p[1].h8 = x;
    p[1].hA = y;
    p[1].hE = 4;
    if (0.0f < r) {
        p[1].hC = 10;
    } else {
        p[1].h4 = 0;
        p[1].hC = 0;
    }
    p[1].h1A = 0;
    p[1].h18 = 0;
    p[1].f10 = p[1].f14 = p[1].h18;
}
