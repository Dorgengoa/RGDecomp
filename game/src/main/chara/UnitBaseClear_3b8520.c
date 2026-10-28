/* rgp:protos */
#define RGP_SELF_UnitBaseClear_3b8520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x10];
    s16 f10;
    s16 pad12;
    s32 f14;
    s16 f18;
    s16 pad1a;
    s32 a1c[2];
    s16 a24[6][2];
    s32 a3c[3][2];
    s16 a54[5][2];
    s16 a68[8][2];
    s16 a88[7][2];
    s32 padA4;
    s16 aA8[4][2];
    u8 padB8[0x10];
    s64 fC8;
    f32 aD0[32];
    s16 a150[32];
    s16 f190;
    s16 f192;
    s16 f194;
    s16 pad196;
    s32 f198;
    u8 b19C_0 : 1;
    u8 b19C_1 : 7;
    u8 pad19d[3];
    s32 f1A0;
    s16 f1A4;
    s16 pad1a6;
    s64 f1A8;
    s32 f1B0;
    s16 f1B4;
    s16 pad1b6;
    s64 f1B8;
    u8 b1C0_0 : 1;
    u8 b1C0_1 : 7;
    u8 pad1c1[3];
    f32 f1C4;
    u8 b1C8_0 : 1;
    u8 b1C8_1 : 1;
    u8 b1C8_2 : 1;
    u8 b1C8_3 : 5;
    u8 pad1c9[3];
    f32 f1CC;
    f32 f1D0;
    s16 f1D4;
    s16 f1D6;
    s16 f1D8;
    s16 f1DA;
    s32 f1DC;
    u8 pad1e0[0xC];
    f32 f1EC;
} Obj;

/*rgp*/
extern s32 D_00465900[4];
extern s32 D_00465910[4];
extern s32 D_00465920[4];
extern s32 D_00465CD0[4];

void UnitBaseClear_3b8520(Obj *o)
{
    s32 i;
    s32 j;

    UnitClearId_3b8a40(o);
    o->f10 = 1;
    o->f14 = 0;
    o->f18 = 0;
    o->f1A0 = 0;
    o->f1A4 = 0;
    o->f1B0 = 0;
    o->f1B4 = 0;
    for (i = 0; i < 2; i++) {
        o->a1c[i] = 0;
        o->a24[0][i] = 0;
        o->a24[1][i] = 0;
        o->a24[2][i] = 0;
        o->a24[3][i] = 0;
        o->a24[4][i] = 0;
        o->a24[5][i] = 0;
        o->a3c[0][i] = 0;
        o->a3c[1][i] = 0;
        o->a3c[2][i] = 0;
        for (j = 0; j < 5; j++) {
            o->a54[j][i] = 0;
        }
        for (j = 0; j < 8; j++) {
            o->a68[j][i] = 0;
        }
        for (j = 0; j < 7; j++) {
            o->a88[j][i] = 0;
        }
        for (j = 0; j < 4; j++) {
            o->aA8[j][i] = 0;
        }
    }
    o->f1DA = 0;
    o->fC8 = 0;
    o->f1A8 = 0;
    o->f1B8 = 0;
    for (i = 0; i < 32; i++) {
        o->aD0[i] = 0.0f;
        o->a150[i] = -1;
    }
    o->f190 = D_00465900[0];
    o->f192 = D_00465910[0];
    o->f194 = D_00465920[0];
    o->f198 = -1;
    o->b19C_0 = 0;
    o->b1C0_0 = 1;
    o->f1C4 = (f32)D_00465CD0[0];
    o->b1C8_0 = 0;
    o->b1C8_1 = 0;
    o->b1C8_2 = 0;
    o->f1CC = 0.0f;
    o->f1D0 = 0.0f;
    o->f1D4 = 0;
    o->f1D6 = 0;
    o->f1D8 = 0;
    o->f1EC = 0.0f;
    o->f1DC = 0;
}
