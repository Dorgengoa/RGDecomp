#include "types.h"
#pragma divbyzerocheck on

typedef unsigned __int128 u128;

typedef struct {
    u128 a;
    u128 b;
} Q32;

typedef struct {
    s32 a;
    s32 b;
} P8;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    u8 x10;
    s32 m14[15];
    Q32 m50[3];
    P8 mB0[8];
    P8 mF0[8];
    P8 m130[8];
    V4 m170;
    P8 m180[8];
    P8 m1C0[8];
    P8 m200[8];
    V4 m240;
    P8 m250[8];
    P8 m290[8];
    P8 m2D0[8];
    P8 m310[12];
    P8 m370[12];
    P8 m3D0[8];
    P8 m410[8];
    P8 m450[8];
    P8 m490[8];
    V4 m4D0;
    V4 m4E0;
} Rec;

typedef struct {
    u8 pad0[0xF20];
    Rec *top;
    u8 padF24[0xC];
    Rec stack[1];
} Ctx;

extern "C" void ViewStackPush_144430(Ctx *self)
{
    Rec *old;

    old = self->top;
    if (old - self->stack < 7) {
        self->top++;
        *self->top = *old;
    }
}
