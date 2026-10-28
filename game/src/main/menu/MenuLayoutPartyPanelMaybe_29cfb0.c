/* rgp:protos */
#define RGP_SELF_MenuLayoutPartyPanelMaybe_29cfb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s16 v[3][8]; } Tbl38;
typedef struct { s16 v[3][7]; } Tbl37;
typedef struct { s16 v[3]; } Tbl3;

typedef struct Item {
    u8 pad0[0x10];
    f32 x10;
    f32 x14;
    s16 x18;
    s16 x1A;
} Item;

typedef struct Box {
    u8 pad0[0x20];
    s16 a[8];
    u8 pad30[0x10];
    s16 b[8];
} Box;

typedef struct Panel {
    u8 pad0[0x4C4];
    s32 h;
} Panel;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_004509A0[];
extern s16 D_004509D0[];
extern s16 D_00450A00[];
extern f32 D_0047D268 __attribute__((section(".sdata")));
extern f32 D_0047D288;
extern f32 D_0047D354 __attribute__((section(".sdata")));
extern f32 D_0047D444 __attribute__((section(".sdata")));
extern f32 D_0047D464 __attribute__((section(".sdata")));
extern f32 D_0047D468 __attribute__((section(".sdata")));
extern f32 D_0047D46C __attribute__((section(".sdata")));
extern f32 D_0047D470 __attribute__((section(".sdata")));
extern s16 D_0047EC28;
extern s16 D_0047EC2A;
extern s16 D_0047EC2C;

s32 MenuLayoutPartyPanelMaybe_29cfb0(Panel *self, s32 id, s32 idx, s32 mode) {
    s16 c[3];
    Tbl38 a __attribute__((aligned(16)));
    Tbl38 b __attribute__((aligned(16)));
    Tbl37 d __attribute__((aligned(16)));
    s32 obj;
    s32 n1;
    s32 n2;
    s32 row;
    Item *it;
    u8 *p;
    Box *q;
    s8 *s;
    s32 sel;
    s32 i;
    u16 t;

    obj = ((s32)GetGameData_1fede0());
    a = *(Tbl38 *)D_004509A0;
    b = *(Tbl38 *)D_004509D0;
    n1 = PartyCountMembers_3c2010(*(s32 *)(obj + 0x18), 1, 1);
    n2 = PartyCountReserve_3c1c20(*(s32 *)(obj + 0x18), 1, 1);
    row = n2 - 5;
    if (row <= 0) {
        row = 0;
    }
    if (mode == 0) {
        if (idx >= n1) {
            idx = n1 - 1;
        }
        p = ((u8 *)UiFindWidget_290460(self->h, id));
        if (p == 0) {
            return 0;
        }
        q = *(Box **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        q->a[0] = a.v[idx][0];
        q->a[1] = a.v[idx][1];
        q->a[2] = a.v[idx][2];
        q->a[3] = a.v[idx][3];
        q->a[4] = a.v[idx][4];
        q->a[5] = a.v[idx][5];
        q->a[6] = a.v[idx][6];
        q->a[7] = a.v[idx][7];
        q->b[0] = b.v[idx][0];
        q->b[1] = b.v[idx][1];
        q->b[2] = b.v[idx][2];
        q->b[3] = b.v[idx][3];
        q->b[4] = b.v[idx][4];
        q->b[5] = b.v[idx][5];
        q->b[6] = b.v[idx][6];
        q->b[7] = b.v[idx][7];
        if (idx == 0) {
            UiSetSpriteSizeUvSize_28f670(self->h, 0xD6, 0, 0, 0, 0, 1);
        } else {
            UiSetSpriteSizeUvSize_28f670(self->h, 0xD6, 0xE, 0xE, 0xE, 0xE, 1);
        }
        if (idx == 2) {
            UiSetSpriteSizeUvSize_28f670(self->h, 0xD6, 0, 0, 0, 0, 6);
        } else {
            UiSetSpriteSizeUvSize_28f670(self->h, 0xD6, 0xE, 0xE, 0xE, 0xE, 6);
        }
        c[0] = D_0047EC28;
        c[1] = D_0047EC2A;
        c[2] = D_0047EC2C;
        UiSetWidgetPos_290f60(self->h, id, c[idx], 0x10);
    } else {
        if (n2 == 0) {
            return 1;
        }
        if (idx >= n2) {
            idx = n2 - 1;
        }
        it = ((Item *)UiGetWidgetSprite_28fe10(self->h, id, 0));
        if (it == 0) {
            return 0;
        }
        if (row == 1) {
            if (idx == 0) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = D_0047D464;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, 0, 4, 0xE, 0x16, 0x5A, 0x5E, 0xE, 8, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x45, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x31, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3F, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3F, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            } else if (idx == 5) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = D_0047D46C;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, -6, 0xC, 0xE, 0xE, 0x80, 0x60, 0xE, 0xE, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x43, 5, 0xE, 0x14, 0x70, 0x5E, 0xE, 8, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x35, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x43, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x43, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            } else {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = 1.0f;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, -6, 0xC, 0xE, 0xE, 0x80, 0x60, 0xE, 0xE, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x40, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x2C, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3A, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3A, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            }
        } else if (row == 2) {
            if (idx == 0) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = D_0047D470;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, 0, 4, 0xE, 0x16, 0x5A, 0x5E, 0xE, 8, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3E, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x2A, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x38, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x38, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            } else if (idx == 6) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = D_0047D268;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, -6, 0xC, 0xE, 0xE, 0x80, 0x60, 0xE, 0xE, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3A, 5, 0xE, 0x14, 0x70, 0x5E, 0xE, 8, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x2C, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3A, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x3A, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            } else {
                UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
                it->x10 = D_0047D444;
                it->x14 = D_0047D468;
                it->x18 = 0x40;
                it->x1A = 0x40;
                UiSetSpritePosSizeUv_28f710(self->h, id, -6, 0xC, 0xE, 0xE, 0x80, 0x60, 0xE, 0xE, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x38, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x24, 0xE, 0x68, 0x66, 8, 0xE, 4);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x32, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x32, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
            }
        } else {
            UiSetSpritePosSizeUv_28f710(self->h, id, 4, 0xC, 0x40, 0x40, 0xC0, 0, 0x40, 0x40, 0);
            it->x10 = D_0047D354;
                it->x14 = D_0047D468;
            it->x18 = 0x40;
            it->x1A = 0x40;
            if (idx == 0) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 0, 4, 0xE, 0x16, 0x5A, 0x5E, 0xE, 8, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x4D, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
            } else {
                UiSetSpritePosSizeUv_28f710(self->h, id, -6, 0xC, 0xE, 0xE, 0x80, 0x60, 0xE, 0xE, 1);
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x4D, 0xC, 0xE, 0xE, 0x8E, 0x60, 0xE, 0xE, 2);
            }
            if (idx == 4) {
                UiSetSpritePosSizeUv_28f710(self->h, id, 0x47, 5, 0xE, 0x14, 0x70, 0x5E, 0xE, 8, 2);
            }
            UiSetSpritePosSizeUv_28f710(self->h, id, 0xE, 0x5F, 0x39, 0xE, 0x68, 0x66, 8, 0xE, 4);
            UiSetSpritePosSizeUv_28f710(self->h, id, 0x47, 0x5F, 0xE, 0xE, 0x70, 0x66, 0xE, 0xE, 5);
            UiSetSpritePosSizeUv_28f710(self->h, id, 0x47, 0x19, 0xE, 0x46, 0x70, 0x5E, 0xE, 8, 7);
        }
        d = *(Tbl37 *)D_00450A00;
        UiSetWidgetPos_290f60(self->h, id, d.v[row][idx], 0xF9);
    }
    s = ((s8 *)MenuGetCursorPos_29fae0(self));
    sel = s[0] + s[1] * 3;
    for (i = 0; i < 10; i++) {
        t = i + 0xDF;
        if (i == sel) {
            UiSetWidgetColor_2905b0(self->h, t, 1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(self->h, t, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        }
    }
    return 0;
}
