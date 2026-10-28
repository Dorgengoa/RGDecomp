/* rgp:protos */
#define RGP_SELF_MenuCatalogTabSetup_360590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Win { u8 pad0[4]; s16 m4; s16 m6; s16 m8; s16 mA; s16 mC; s16 mE; s16 m10; s16 m12; s16 m14; s16 m16; s16 m18; s16 m1A; } Win;
typedef struct Self {
    u8 pad0[0x1D4];
    f32 m1D4;
    u8 m1D8[0x9C];
    void *m274;
    s32 m278;
    u8 pad27C[8];
    s32 m284;
    s32 m288;
    s32 m28C;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D458 __attribute__((section(".sdata")));
extern u8 D_004DB1D0[];

void MenuCatalogTabSetup_360590(Self *self)
{
    Win *t;

    self->m288 = 0;
    self->m28C = 0;
    UiSetWidgetVisible_290010(self->m274, 0x1F7, 1, -1);
    UiSetWidgetVisible_290010(self->m274, 0x1F8, 1, -1);
    UiSetWidgetVisible_290010(self->m274, 0x1EA, 0, -1);
    UiSetWidgetVisible_290010(self->m274, 0x1EC, 0, -1);
    UiSetWidgetVisible_290010(self->m274, 0x1ED, 0, -1);
    UiSetWidgetVisible_290010(self->m274, 0x20D, 0, -1);
    UiSetWidgetVisible_290010(self->m274, 0x20E, 0, -1);
    UiSetWidgetsVisibleById_291110(self->m274, 0x1F0, 0, 1);
    UiSetWidgetsVisibleById_291110(self->m274, 0x1F1, 0, 1);
    UiSetWidgetVisible_290010(D_004DB1D0, 5, 0, -1);
    UiSetWidgetVisible_290010(D_004DB1D0, 6, 0, -1);
    UiSetSpriteV_28f8f0(self->m274, 0x1EE, 0, 0);
    t = (((Win *)UiEntryListFindByTag_28ea40(self->m278, 0x24)));
    t->m4 = 0;
    t->m6 = 0;
    t->m8 = 0;
    t->mA = 0;
    t->m14 = 0;
    t->m16 = 0;
    t->m18 = 0;
    t->m1A = 0;
    self->m1D4 = D_0047D458;
    switch (self->m284) {
    case 0:
        UiSetWidgetVisible_290010(self->m274, 0x1EA, 1, -1);
        UiSetWidgetVisible_290010(self->m274, 0x20D, 1, -1);
        t->m4 = 0x6E;
        t->m6 = 0x77;
        t->m8 = 0x54;
        t->mA = 0x59;
        t->mC = 3;
        t->mE = 2;
        t->m10 = 3;
        t->m12 = 2;
        UiSetWidgetPos_290f60(self->m274, 0x20D, t->m4, t->m6);
        UiSelFrameSetPos_28daa0(self->m1D8, 0x1F6, 0x1E, 0x22);
        MenuCatalogItemGridSetup_35e570(self);
        break;
    case 1:
        UiSetWidgetVisible_290010(self->m274, 0x1EC, 1, -1);
        UiSetWidgetVisible_290010(self->m274, 0x20E, 1, -1);
        t->m4 = 0;
        t->m6 = 0x21;
        t->m8 = 0;
        t->mA = 0x2D;
        t->mC = 0;
        t->mE = 5;
        t->m10 = 0;
        t->m12 = 5;
        UiSetWidgetPos_290f60(self->m274, 0x20E, t->m4, t->m6);
        UiSetWidgetPos_290f60(self->m274, 0x1F4, 0x1F, 0x21);
        MenuCatalogBountyTabLayoutMaybe_35de80(self);
        break;
    case 2:
        UiSetWidgetVisible_290010(self->m274, 0x1ED, 1, -1);
        UiSetWidgetVisible_290010(self->m274, 0x20E, 1, -1);
        t->m4 = 0;
        t->m6 = 0x1D;
        t->m8 = 0;
        t->mA = 0x1B;
        t->mC = 0;
        t->mE = 9;
        t->m10 = 0;
        t->m12 = 9;
        UiSetWidgetPos_290f60(self->m274, 0x20E, t->m4, t->m6);
        UiSetWidgetPos_290f60(self->m274, 0x1F5, 0x1F, 0x21);
        MenuCatalogRankListSetup_35da20(self);
        break;
    case 3:
        UiSetWidgetVisible_290010(self->m274, 0x1F7, 0, -1);
        UiSetWidgetVisible_290010(self->m274, 0x1F8, 0, -1);
        UiSetWidgetVisible_290010(D_004DB1D0, 5, 1, -1);
        UiSetSpriteV_28f8f0(self->m274, 0x1EE, 0x40, 0);
        break;
    case 4:
        UiSetWidgetVisible_290010(self->m274, 0x1F7, 0, -1);
        UiSetWidgetVisible_290010(self->m274, 0x1F8, 0, -1);
        UiSetWidgetVisible_290010(D_004DB1D0, 6, 1, -1);
        UiSetSpriteV_28f8f0(self->m274, 0x1EE, 0x40, 0);
        break;
    }
}
