/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpOpen_4f1f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
} B;

typedef struct C {
    s32 f00;
} C;

typedef struct A {
    u8    pad00[0x5C];
    f32   f5C;
    s32   f60;
    s32   f64;
    s16   f68;
    u8    f6A;
    u8    pad6B[0x5];
    u8    f70;
    u8    f71;
    u8    pad72[0x2];
    s16  *f74;
    s32   f78;
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
    void *f8C;
} A;

extern f32 D_0047D4F4;
extern s8  factory_D_0050BD60[];
extern void *D_004807E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpOpen_4f1f80(A *o)
{
    B  *b;
    C  *c;
    s8  t[32] __attribute__((aligned(16)));
    s8 *sp;
    s8 *dp;
    s32 i;

    o->f60 = 0;
    o->f64 = 0;
    o->f5C = -3.1415927f;
    o->f70 = 0;
    b = ((B *)UiEntryListFindByTag_28ea40(o->f8C, 0x8944));
    UiSetWidgetPos_290f60(o->f88, 0x83, b->f04, b->f06);
    UiSetWidgetPos_290f60(o->f88, 0x82, 0x1A, 0x3E);
    c = ((C *)FactoryGetRequestPtr_367ec0());
    c->f00 = 0xC;
    o->f6A = 0;
    factory_FactoryHelpTopicListBuild_4f1350(o);
    o->f71 = 1;
    sp = factory_D_0050BD60;
    dp = t;
    for (i = 0x10; i > 0; i--) {
        dp[0] = sp[0];
        dp[1] = sp[1];
        sp += 2;
        dp += 2;
    }
    for (i = 0; i < 0x10; i++) {
        o->f74[i * 2] = t[i * 2];
        o->f74[i * 2 + 1] = t[i * 2 + 1];
    }
    factory_FactoryMenuTexRelease_4ec090();
    o->f7C = -1;
    o->f80 = 0;
    o->f78 = 0;
    UiSetWidgetVisible_290010(o->f88, 0x84, 0, -1);
    UiSetWidgetVisible_290010(o->f88, 0x85, 0, -1);
    UiSetWidgetVisible_290010(D_004807E8, 0x96, 0, -1);
    o->f68 = 1;
    UiSetWidgetAlpha_2907a0(o->f88, 0x84, 0.0f);
    UiSetWidgetAlpha_2907a0(o->f88, 0x85, 0.0f);
}
