#include "types.h"

struct Rec {
    s16 m0;
    u8 pad2[0xA];
    s32 mC;
};

class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual Rec *v26(s32);
};

struct Mgr {
    u8 pad0[0x8];
    Obj *m8;
};

struct Sys {
    u8 pad0[0x40];
    Mgr *m40;
};

struct Ctx {
    u8 pad0[0x8];
    Sys *m8;
    u8 padC[0xC];
    s32 m18;
};

struct Val {
    u8 pad0[0x8];
    s64 m8;
};

struct Dst {
    u8 pad0[0x4];
    s32 m4;
};

struct Ent {
    u8 pad0[0x24];
    Val *m24;
    Dst *m28;
};

extern "C" {
Ctx *GetGameData_1fede0(void);
s32 MsgTableLookup_28aa30(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
Ent *UiFindWidget_290460(s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 InvCountById_3c78d0(s32, s32, s32, s32);
s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
s32 SkillFlowCountByItemMaybe_3e97c0(Ctx *, s32, s32, s32, s32, s32, s32);
Rec *RevelationBoardCellGetItemRec_3ead00(Ctx *, s32, s32);
s32 RevelationBoardGetCells_3eb510(Ctx *, s32);
extern f32 D_0047D5D0;
extern s32 D_0047F6C4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_0048238C;
extern s32 D_004823D8;
extern s32 D_00482E30;
extern s16 D_00482E38;
}

static inline void Apply(Ctx *ctx, Rec *a, Rec *b) {
    Ent *e;
    Dst *d;
    Val *v;

    e = UiFindWidget_290460(D_00482360, 0x60);
    if (e != 0) {
        d = e->m28;
        if (d != 0 && a != 0) {
            d->m4 = a->mC;
        }
    }
    e = UiFindWidget_290460(D_00482360, 0x61);
    if (e != 0) {
        v = e->m24;
        if (v != 0) {
            v->m8 = InvCountById_3c78d0(ctx->m18, a->m0, 0, 0);
        }
    }
    e = UiFindWidget_290460(D_00482360, 0x62);
    if (e != 0) {
        v = e->m24;
        if (v != 0) {
            v->m8 = SkillFlowCountByItemMaybe_3e97c0(ctx, b->m0, -1, 0, 1, 1, 0);
        }
    }
}

extern "C" s32 MenuRevelationConfirmOpenState_3476a0(s32 arg0, s32 arg1) {
    s32 sp5C;
    s32 sp58;
    Ctx *ctx;
    s16 *pos;
    Rec *rec;
    Rec *rec2;
    s32 base;

    if (arg1 != 0) {
        UiSetTextString_28f510(D_00482360, 0x5F, MsgTableLookup_28aa30(D_004823D8, 0x1037), 0);
        UiSetTextString_28f510(D_00482360, 0x61, MsgTableLookup_28aa30(D_004823D8, 0x1038), 0);
        UiSetTextString_28f510(D_00482360, 0x62, MsgTableLookup_28aa30(D_004823D8, 0x1039), 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5D, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x63, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x5D, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x5D, 1.0f, D_0047D5D0, -1.0f);
        UiGetWidgetPos_2910a0(D_00482360, 0x5A, &sp5C, &sp58);
        UiSetWidgetPos_290f60(D_00482360, 0x5D, 0x75, sp58 + 0x37);
        UiSetWidgetPos_290f60(D_00482360, 0x63, -0x14, 8);
        D_00482E30 = 0;
        D_00482E38 = 0;
        ctx = GetGameData_1fede0();
        if (ctx == 0) {
            return 0;
        }
        pos = (s16 *)(D_0048238C + 0x10);
        base = RevelationBoardGetCells_3eb510(ctx, D_0047F6C4);
        rec = RevelationBoardCellGetItemRec_3ead00(ctx, D_0047F6C4, base + (pos[0] + pos[1] * 26) * 4);
        if (rec->m0 == 0x40F2 || rec->m0 == 0x410B) {
            if (InvHasItemInCategory_3c7f40(ctx->m18, 0x40F2, 0, 0) != 0) {
                Apply(ctx, rec, rec);
            } else if (InvHasItemInCategory_3c7f40(ctx->m18, 0x410B, 0, 0) != 0) {
                rec2 = ctx->m8->m40->m8->v26(0x410B);
                Apply(ctx, rec2, rec);
            }
        } else {
            Apply(ctx, rec, rec);
        }
    }
    if (!(UiGetWidgetAlpha_290770(D_00482360, 0x5D) < 1.0f)) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1B, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x63, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x63, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x63, 1.0f, D_0047D5D0, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x74, 0);
    }
    return 1;
}
