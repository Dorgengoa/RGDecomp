/* rgp:protos */
#define RGP_SELF_SoundCategoryTableInitMaybe_1bbbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8 b0;
    u8 p1[3];
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 x14;
    u8 x15;
    u8 x16;
    u8 x17;
    s32 x18;
    s32 x1C;
    s32 x20;
} Ent;

typedef struct G {
    s32 mode;
    u8 flag;
    u8 p5[3];
    Ent ent[16];
    s32 idx[16];
} G;

extern G D_0049E880;

void SoundCategoryTableInitMaybe_1bbbb0(s32 arg0)
{
    s32 i;
    u32 t;
    Ent *e3;
    Ent *e5;
    Ent *e9;
    Ent *e10;
    Ent *e6;
    Ent *e7;
    Ent *e0;
    Ent *e1;
    Ent *e2;
    Ent *e12;
    Ent *e4;

    D_0049E880.mode = 0x40;
    D_0049E880.flag = 0;
    for (i = 0; i < 16; i++) {
        D_0049E880.ent[i].b0 = 0;
        D_0049E880.ent[i].x4 = 0;
        D_0049E880.ent[i].x8 = 0;
        D_0049E880.ent[i].x18 = 0;
        D_0049E880.ent[i].xC = 0;
        D_0049E880.ent[i].x10 = -1;
        D_0049E880.ent[i].x14 = 0;
        D_0049E880.ent[i].x15 = 0;
        D_0049E880.ent[i].x16 = 0;
        D_0049E880.ent[i].x17 = 0;
        D_0049E880.ent[i].x1C = -1;
        D_0049E880.ent[i].x20 = -1;
        D_0049E880.idx[i] = i;
    }
    t = arg0 & 0xFF;
    switch (t) {
    case 2:
    case 3:
        D_0049E880.mode = 0x2800;
        for (i = 0; i < 16; i++) {
            D_0049E880.ent[i].x4 = 1;
        }
        D_0049E880.ent[2].x4 = -1;
        D_0049E880.ent[1].x4 = -1;
        D_0049E880.ent[7].x4 = -1;
        D_0049E880.ent[6].x4 = -1;
        D_0049E880.ent[4].x4 = -1;
        D_0049E880.ent[10].x4 = 0;
        if (t != 3) {
            D_0049E880.ent[0].x8 = 0x87000;
        }
        D_0049E880.ent[6].x8 = 0x19000;
        D_0049E880.ent[11].x10 = 0;
        break;
    case 4:
    case 5:
        D_0049E880.mode = 0x400;
        D_0049E880.flag = 1;
        e0 = &D_0049E880.ent[0];
        D_0049E880.ent[8].b0 = 1;
        D_0049E880.ent[11].b0 = 1;
        e1 = &D_0049E880.ent[1];
        e10 = &D_0049E880.ent[10];
        e3 = &D_0049E880.ent[3];
        e3->x4 = 1;
        e3->x14 = 1;
        e2 = &D_0049E880.ent[2];
        e4 = &D_0049E880.ent[4];
        e5 = &D_0049E880.ent[5];
        e9 = &D_0049E880.ent[9];
        e7 = &D_0049E880.ent[7];
        e12 = &D_0049E880.ent[12];
        e6 = &D_0049E880.ent[6];
        e9->x4 = 1;
        e9->x14 = 1;
        e5->x4 = 1;
        e5->x14 = 1;
        e10->x4 = 0;
        e10->x16 = 1;
        e7->xC = 0x16000;
        e10->x17 = 1;
        e6->x8 = 0x19000;
        e7->x8 = e7->xC * 3;
        e0->b0 = 1;
        e1->x4 = -1;
        e1->x14 = 1;
        e2->x4 = -1;
        e7->xC = 0x16000;
        e12->x4 = -1;
        e4->x4 = -1;
        e7->x4 = -1;
        e2->x15 = 1;
        e6->x4 = -1;
        e7->x14 = 1;
        e6->x14 = 1;
        e2->x8 = 0x18800;
        e12->x8 = 0x18800;
        e12->x15 = 1;
        e4->x15 = 1;
        e4->x14 = 1;
        if (t == 5) {
            e0->b0 = 0;
            e0->x4 = 1;
            e0->x15 = 1;
            e0->x14 = 0;
        }
        D_0049E880.idx[0] = 6;
        D_0049E880.idx[1] = 9;
        D_0049E880.idx[2] = 7;
        D_0049E880.idx[3] = 3;
        D_0049E880.idx[4] = 2;
        D_0049E880.idx[5] = 12;
        D_0049E880.idx[6] = 5;
        D_0049E880.idx[7] = 1;
        D_0049E880.idx[8] = 4;
        D_0049E880.idx[9] = 10;
        D_0049E880.idx[10] = 0;
        D_0049E880.idx[11] = 8;
        D_0049E880.idx[12] = 11;
        break;
    case 0:
    case 1:
    default:
        D_0049E880.mode = 0x40;
        for (i = 0; i < 16; i++) {
            D_0049E880.ent[i].x4 = -1;
        }
        D_0049E880.ent[0].x4 = 1;
        D_0049E880.ent[11].x4 = 1;
        D_0049E880.ent[10].x4 = 0;
        break;
    }
}
