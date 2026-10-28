/* rgp:protos */
#define RGP_SELF_MenuItemUseTargetSelFrameLayout_2a0a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad00[0x10];
    f32 f10;
    f32 f14;
    u8 pad18[0x42 - 0x18];
    s16 h42;
    u8 pad44[2];
    s16 h46;
    u8 pad48[0x62 - 0x48];
    s16 h62;
    u8 pad64[0x80 - 0x64];
    s16 h80;
    u8 pad82[2];
    s16 h84;
    u8 pad86[0xA2 - 0x86];
    s16 hA2;
    s16 hA4;
    u8 padA6[0xC0 - 0xA6];
    s16 hC0;
    u8 padC2[0xE0 - 0xC2];
    s16 hE0;
    u8 padE2[4];
    s16 hE6;
    u8 padE8[0x100 - 0xE8];
    s16 h100;
    s16 h102;
} Obj;

typedef struct Tbl {
    s16 v[3][7];
} Tbl;

typedef struct Ctx {
    u8 pad[0x18];
    s32 x18;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00451000[0x400];
extern f32 D_0047D478 __attribute__((section(".sdata")));
extern f32 D_0047D47C __attribute__((section(".sdata")));
extern f32 D_0047D480 __attribute__((section(".sdata")));
extern s16 D_0047EC38 __attribute__((section(".sdata")));
extern s16 D_0047EC3A __attribute__((section(".sdata")));
extern s16 D_0047EC3C __attribute__((section(".sdata")));

s32 MenuItemUseTargetSelFrameLayout_2a0a60(s32 *arg0, s16 arg1, s16 arg2, s32 arg3) {
    Tbl tbl __attribute__((aligned(16)));
    volatile s16 base[3];
    Obj *p;
    s32 n;
    s32 v;
    s16 t;

    p = ((Obj *)UiGetWidgetSprite_28fe10(*arg0, 0x8E, 0));
    if (p == 0) {
        return 0;
    }
    if (arg2 == 0) {
        UiSetWidgetPos_290f60(*arg0, 0x8E, arg1 * 0x83 + 0x11, 0x10);
        if (arg3 == 0) {
            p->f10 = 2.0f;
            p->f14 = D_0047D478;
            p->hE6 = 0x56;
            p->h46 = 0x56;
            p->hA4 = 0x6E;
            p->h84 = 0x6E;
        } else if (arg3 == 2) {
            p->f10 = D_0047D47C;
            p->f14 = D_0047D478;
            p->hE6 = 0x56;
            p->h46 = 0x56;
            p->hA4 = 0x174;
            p->h84 = 0x174;
        } else if (arg3 == 3) {
            p->f10 = D_0047D47C;
            p->f14 = 3.0f;
            p->hE6 = 0xB1;
            p->h46 = 0xB1;
            p->hA4 = 0x174;
            p->h84 = 0x174;
        }
    } else if (arg2 == 1) {
        base[0] = D_0047EC38;
        base[1] = D_0047EC3A;
        base[2] = D_0047EC3C;
        tbl = *(Tbl *)D_00451000;
        n = PartyCountReserve_3c1c20(((Ctx *)GetGameData_1fede0())->x18, 1, 1) - 5;
        if (n <= 0) {
            n = 0;
        }
        v = base[n];
        if ((n == 1 && (arg1 == 0 || arg1 == 5)) || (n == 2 && (arg1 == 0 || arg1 == 6))) {
            v += 4;
        }
        UiSetWidgetPos_290f60(*arg0, 0x8E, tbl.v[n][arg1] + 0x11, 0x78);
        p->f10 = (f32)(v + 0x12) / 64.0f;
        p->hA4 = v;
        p->h84 = v;
        p->f14 = D_0047D480;
        p->hE6 = 0x49;
        p->h46 = 0x49;
    }
    t = p->h42 + p->h46;
    p->h102 = t;
    p->hA2 = t;
    p->h62 = t;
    t = p->h80 + p->h84;
    p->h100 = t;
    p->hE0 = t;
    p->hC0 = t;
    return 1;
}
