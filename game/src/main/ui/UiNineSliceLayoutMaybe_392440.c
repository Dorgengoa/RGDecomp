/* rgp:protos */
#define RGP_SELF_UiNineSliceLayoutMaybe_392440 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct I3 { s32 v[3]; } I3;
typedef struct F3 { f32 v[3]; } F3;

typedef struct Elem {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
    f32 m10;
    f32 m14;
    s16 m18;
    s16 m1A;
    u8 pad1C[4];
} Elem;

typedef struct Obj {
    u8 pad0[0x20];
    Elem *m20;
} Obj;

extern f32 D_0047FEC0[3] __attribute__((section(".sdata")));
extern f32 D_0047FEC4 __attribute__((section(".sdata")));
extern f32 D_0047FEC8 __attribute__((section(".sdata")));
extern f32 D_0047FED0[3] __attribute__((section(".sdata")));
extern f32 D_0047FED4 __attribute__((section(".sdata")));
extern f32 D_0047FED8 __attribute__((section(".sdata")));
extern f32 D_0047FEE0[3] __attribute__((section(".sdata")));
extern f32 D_0047FEE4 __attribute__((section(".sdata")));
extern f32 D_0047FEE8 __attribute__((section(".sdata")));
extern f32 D_0047FEF0[3] __attribute__((section(".sdata")));
extern f32 D_0047FEF4 __attribute__((section(".sdata")));
extern f32 D_0047FEF8 __attribute__((section(".sdata")));
extern s32 D_004641A8[4];
extern s32 D_004641B8[4];
extern s32 D_004641C8[4];
extern s32 D_004641D8[4];

void UiNineSliceLayoutMaybe_392440(s32 arg0, Obj *arg1, s32 arg2, s32 arg3)
{
    union { I3 i; F3 f; } Wu;
    union { I3 i; F3 f; } Hu;
    union { I3 i; F3 f; } Xu;
    union { I3 i; F3 f; } Yu;
    Elem *e;
    s32 i;
    s32 col;
    s32 row;
    s16 z;

    if (arg1 == NULL) {
        return;
    }
    e = arg1->m20;
    if (e == NULL) {
        return;
    }
    Wu.f = *(const F3 *)D_0047FEC0;
    Wu.i.v[1] = arg2 - 0x20;
    Hu.f = *(const F3 *)D_0047FED0;
    Hu.i.v[1] = arg3 - 0x20;
    Xu.f = *(const F3 *)D_0047FEE0;
    Xu.i.v[2] = arg2 - 0x10;
    Yu.f = *(const F3 *)D_0047FEF0;
    Yu.i.v[2] = arg3 - 0x10;
    z = 0;
    for (i = 0; i < 9; i++, e++) {
        col = i % 3;
        row = i / 3;
        if (col == 1 && row == 1) {
            continue;
        }
        e->m0 = Xu.i.v[col];
        e->m2 = Yu.i.v[row];
        e->m8 = D_004641A8[col];
        e->mA = D_004641B8[row];
        e->m4 = Wu.i.v[col];
        e->m6 = Hu.i.v[row];
        e->mC = D_004641C8[col];
        e->mE = D_004641D8[row];
        e->m1A = 0;
        e->m18 = 0;
        e->m10 = e->m14 = e->m18;
    }
}
