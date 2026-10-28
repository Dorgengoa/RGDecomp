/* rgp:protos */
#define RGP_SELF_normal_FieldHudInit_4f71a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F71A0 -- the main gameplay object's constructor.  1,324 bytes.
 *
 * `(u16)(i*7 + 0xC)` is used by TWO consecutive calls and so is a named local
 * (retail's `$16`), while the single-use ids are passed inline and picked up by
 * the callee's own u16 parameter -- that is what the `andi $5, $2, 0xFFFF` at
 * each call site says.
 * D_00484414's element size is 0x310, which is the same constant handed to
 * func_100710 as the array stride; `sll/subu/sll/subu/sll` is mwcc's
 * strength-reduced multiply by it.
 * `normal_FieldHudGlowListCtor_4f76d0` is taken by ADDRESS as a callback -- written as the
 * symbol, not a cast literal, or it would compile to lui/ori. */
typedef struct A8 { s32 f0; s16 f4; s16 f6; } A8;
typedef struct A4 { s16 f0; s16 f2; } A4;
typedef struct W  { u8 pad00[4]; void *f04; } W;
typedef struct H  { u8 pad00[0x28]; W *f28; } H;
typedef struct T310 { u8 pad000[0x310]; } T310;

typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;

typedef struct Obj {
    u8    pad000[8];
    s32   f008;
    u8    pad00C[0x14 - 0x0C];
    u8    f014;
    u8    pad015[0x1C - 0x15];
    s32   f01C;
    u8    pad020[0x28 - 0x20];
    u8    f028;
    u8    pad029[0x2B0 - 0x29];
    s16   f2B0;
    u8    pad2B2[0x2BA - 0x2B2];
    s16   f2BA[3];
    f32   f2C0[3];
    f32   f2CC[3];
    u8    pad2D8[0x33C - 0x2D8];
    A8    f33C[3];
    A4    f354[3];
    s8    f360;
    s8    f361;
    s8    f362;
    u8    pad363[1];
    s32   f364;
    s32   f368;
    s32   f36C;
    s32   f370;
    u8    pad374[4];
    s16   f378;
    s16   f37A;
    s16   f37C;
    u8    pad37E[2];
    s16   f380;
    u8    pad382[0x3A2 - 0x382];
    s16   f3A2;
    u8    pad3A4[0x3AC - 0x3A4];
    s16   f3AC;
    s8    f3AE;
    u8    pad3AF[1];
    s16   f3B0;
    s16   f3B2;
    u8    pad3B4[4];
    void *f3B8[4];
    void *f3C8;
    u8    pad3CC[0x3D4 - 0x3CC];
    s32   f3D4;
    u8    pad3D8[4];
    s16   f3DC;
} Obj;

extern u8 normal_D_00524DE0[];
extern u8 normal_D_00524FA0[];
extern void  *D_00484410;
extern T310  *D_00484414;

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
extern void  memcpy(void *a, const void *b, s32 c);
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
extern void  memset(void *a, s32 b, s32 c);
/*rgp*/
/*rgp*/

void normal_FieldHudInit_4f71a0(Obj *p, void *heap)
{
    void *g;
    Rec *r;
    void *t;
    s32 n;
    u8 *q;
    s32 i;
    s32 j;
    s32 k;
    u8 *qb;
    s32 d;
    u16 id;
    H *h;
    W *w;

    p->f378 = 1;
    p->f37A = 0;
    p->f37C = 0;
    p->f380 = 0;
    p->f3B0 = 0;
    p->f3B2 = 0;
    p->f3AC = 0;
    p->f3AE = 0;
    p->f3D4 = -1;
    p->f3A2 = 0;
    D_00484410 = SceneSoundGetSlot0HandleCur_207df0();
    g = GetMenuResGroup_206a40();
    r = ((Rec *)ResGroupListFindById_42c500(g, 0x10));
    t = r->f04;
    n = r->fA_hi;
    BattleSparkBurstReset_382fc0(&p->f028);
    UiWidgetListReset_2912e0(&p->f014);
    UiInitWidgetPool_290390(&p->f014, heap, n);
    UiAddWidgets_2901d0(&p->f014, t, 0);
    p->f01C = 0x32B;
    UiTextStyleReset_290450();
    UiSetWidgetVisible_290010(&p->f014, 1, 0, -1);
    p->f3DC = 0;
    r = ((Rec *)ResGroupListFindById_42c500(g, 0x11));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(p);
    UiInitWidgetPool_290390(p, heap, n);
    UiAddWidgets_2901d0(p, t, 0);
    p->f008 = 0x32B;
    UiTextStyleReset_290450();

    for (i = 0; i < 3; i++) {
        q = ((u8 *)MemStackAllocQw_14d950(heap, 0x1C));
        UiSetWidgetSprites_290b90(p, i + 3, q);
        memcpy(q, normal_D_00524DE0, 0x1C0);
    }
    qb = ((u8 *)MemStackAllocQw_14d950(heap, 0x40));
    for (i = 0; i < 0x10; i++) {
        UiSetWidgetSprites_290b90(p, i + 0x2E, qb);
        memcpy(qb, normal_D_00524FA0, 0x20);
        *(s16 *)(qb + 0x20) = -1;
        qb += 0x40;
    }
    p->f3C8 = MemStackNew_14e1b0(0x24E, heap);
    for (i = 0; i < 4; i++) {
        p->f3B8[i] = ((u8 *)MemStackAllocQw_14d950(heap, 4));
    }
    normal_FieldHudLogReset_4f8dd0(p);
    UiSetWidgetVisible_290010(p, 6, 1, -1);
    UiSetWidgetVisible_290010(p, 0xD, 1, -1);
    UiSetWidgetVisible_290010(p, 0x14, 1, -1);
    UiSetWidgetVisible_290010(p, 3, 1, -1);
    UiSetWidgetVisible_290010(p, 4, 1, -1);
    UiSetWidgetVisible_290010(p, 5, 1, -1);
    UiSetWidgetVisible_290010(p, 0x24, 1, -1);
    UiSetWidgetPos_290f60(p, 0x24, 0xDF, 0x15);
    normal_FieldHudTacticsModeIconRefresh_4f7be0(p);
    D_00484414 = ConstructNewArray_100710(MemStackNew_14e1b0(0x940, heap), normal_FieldHudGlowListCtor_4f76d0,
                             0, 0x310, 3);
    for (d = 0; d < 3; d++) {
        k = d * 7;
        normal_FieldHudPartyPanelLayoutMaybe_4f7700(p, k + 6, d, 1);
        p->f33C[d].f4 = 0;
        p->f33C[d].f0 = 0;
        p->f33C[d].f6 = -1;
        p->f354[d].f0 = 0;
        p->f354[d].f2 = -1;
        id = k + 0xC;
        p->f2CC[d] = 1.0f;
        UiSetWidgetAlpha_2907a0(p, id, 1.0f);
        UiSetWidgetsVisibleById_291110(p, id, 0, 1);
        if (D_00484414 != 0) {
            UiGlowSpriteListReset_33c040(&D_00484414[d]);
        }
    }
    UiSetWidgetPos_290f60(p, 6, -0x140, 0x17C);
    UiSetWidgetPos_290f60(p, 0xD, -0x140, 0x17C);
    UiSetWidgetPos_290f60(p, 0x14, -0x140, 0x17C);
    UiSetWidgetPos_290f60(p, 3, 0x26, 0x16F);
    UiSetWidgetPos_290f60(p, 4, 0xA3, 0x16F);
    UiSetWidgetPos_290f60(p, 5, 0x120, 0x16F);
    normal_FieldHudPartyPanelsRefresh_4f7d00(p);
    p->f2B0 = 0;
    for (j = 0; j < 3; j++) {
        p->f2BA[j] = 0;
        p->f2C0[j] = -1.0f;
    }
    p->f364 = 0;
    p->f368 = 0;
    p->f36C = 0;
    p->f370 = 0;
    normal_FieldHudPanelsClearMaybe_4f70d0(p);
    for (i = 0; i < 4; i++) {
        memset(p->f3B8[i], 0, 0x40);
        id = i + 0x7A;
        UiSetWidgetPos_290f60(p, id, 0, i * 30);
        h = ((H *)UiFindWidget_290460(p, id));
        if (h != 0) {
            w = h->f28;
            if (w != 0) {
                w->f04 = p->f3B8[3 - i];
            }
        }
    }
    p->f362 = 0;
    p->f361 = 0;
    p->f360 = 0;
    normal_FieldHudLogClose_4f88b0(p);
}
