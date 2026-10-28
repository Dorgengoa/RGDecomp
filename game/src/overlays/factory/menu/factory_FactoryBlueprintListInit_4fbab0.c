/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintListInit_4fbab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
} B;

typedef struct A {
    u8    pad00[0x5C];
    s16   f5C;
    s16   f5E;
    s16   f60;
    s16   f62;
    f32   f64;
    u8    pad68[0x4];
    u8    f6C;
    u8    pad6D[0x3];
    s32   f70;
    s32   f74;
    s16   f78;
    s16   f7A;
    u8    f7C;
    u8    pad7D[0x3];
    void *f80;
    void *f84;
    u8    pad88[0xC];
    s32   f94;
    u8    f98[0x20];
} A;

extern f32   D_0047D4F4;
extern void *D_004807E8;
extern void *D_004807EC;
extern void *D_00484A70;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintListInit_4fbab0(A *o)
{
    f32 v;
    B *b;

    v = D_0047D4F4;
    o->f94 = 0;
    o->f64 = -3.1415927f;
    UiSelFrameReset_28db70(&o->f98);
    UiSelFrameInit_28da30(&o->f98, o->f80, 0x26);
    UiSelFrameSetRect_28db40(&o->f98, 0x26, 0x1A, 0x1A, 0x32, 0x38, 0, 0);
    UiSelFrameCalcTileCounts_28d9d0(&o->f98);
    UiSelFrameSetScrollPeriod_28d9c0(&o->f98, 1);
    UiSelFrameSetPos_28daa0(&o->f98, 0x26, 0x1A, 0x1A);
    UiSelFrameAnimStep_28d820(&o->f98, 0x26);
    b = ((B *)UiEntryListFindByTag_28ea40(o->f84, 0x88CC));
    UiSetWidgetPos_290f60(o->f80, 0x40, b->f04, b->f06);
    UiSetWidgetsVisibleById_291110(D_004807EC, 0x97, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004807EC, 0x97, 1.0f);
    factory_FactoryBlueprintMarkCell_4f7a40(o, 0, 0);
    UiSetWidgetsVisibleById_291110(o->f80, 0x23, 0, 1);
    UiSetWidgetVisible_290010(o->f80, 0x27, 0, -1);
    UiSetWidgetVisible_290010(o->f80, 0x2B, 0, -1);
    if (o->f70 != 0) {
        UiSetWidgetPos_290f60(o->f80, 0x29, 0, 0);
        UiSetWidgetVisible_290010(o->f80, 0x29, 1, -1);
    } else {
        UiSetWidgetPos_290f60(o->f80, 0x29, 0xEB, 0);
        UiSetWidgetVisible_290010(o->f80, 0x29, 0, -1);
    }
    UiSetWidgetVisible_290010(D_004807E8, 0x92, 0, -1);
    UiSetWidgetAlpha_2907a0(o->f80, 0x27, 1.0f);
    o->f7C = 0;
    o->f5C = 0;
    o->f5E = 0;
    o->f60 = 0;
    o->f62 = 0;
    o->f74 = 0;
    o->f78 = 0;
    o->f7A = 0;
    o->f6C = 0;
    factory_FactoryBlueprintGridBuild_4f9f50(o);
    UiSetTextString_28f510(o->f80, 0x39, MsgTableLookup_28aa30(D_00484A70, 0), 0);
    UiSetTextString_28f510(o->f80, 0x39, MsgTableLookup_28aa30(D_00484A70, 1), 1);
    UiSetTextString_28f510(o->f80, 0x39, MsgTableLookup_28aa30(D_00484A70, 2), 2);
    UiSetTextString_28f510(o->f80, 0x39, MsgTableLookup_28aa30(D_00484A70, 3), 3);
    UiSetTextString_28f510(o->f80, 0x39, MsgTableLookup_28aa30(D_00484A70, 4), 5);
    UiSetTextString_28f510(o->f80, 0x3A, MsgTableLookup_28aa30(D_00484A70, 3), 0);
    UiSetTextString_28f510(o->f80, 0x3A, MsgTableLookup_28aa30(D_00484A70, 0x1D), 3);
    UiSetSpriteFlags_290bd0(o->f80, 0x29, (long long)(0x200), 1, 0, 0);
    UiSetSpriteFlags_290bd0(o->f80, 0x29, (long long)(0x200), 1, 1, 0);
    UiSetTextString_28f510(o->f80, 0x29, MsgTableLookup_28aa30(D_00484A70, 0x32), 0);
}
