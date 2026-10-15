#include "types.h"

class Obj {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual s32 v05C();
    s32 pad4;
    s32 pad8;
    s32 wC;
};

typedef struct G {
    u8 pad[0x18];
    s32 w18;
} G;

typedef struct Cfg {
    u8 pad[0x6C];
    s8 b6C;
} Cfg;

typedef struct Ui {
    u8 pad[0x7A2];
    s8 b7A2;
} Ui;

extern "C" {
G *GetGameData_1fede0(void);
s32 SceneSoundGetSlot0HandleCur_207df0(void);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void RevelationBoardSetCharaPortrait_349660(Obj *);
void RevelationBoardCursorUpdateMaybe_34d080(Ui *, s32, s32, s32);
void RevelationBoardStateInit_34da10(Ui *, s32);
Obj *PartyGetSlotChara_3c2fb0(s32, s8);
extern f32 D_0047D628;
extern f32 D_0047D634;
extern f32 D_0047D638;
extern s32 D_0047F6C0;
extern s32 D_0047F6C4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern Cfg *D_00482378;
extern Ui *D_0048238C;
extern s8 D_00482E10;
extern s8 D_00482E14;
extern s32 D_00482E18;
extern s32 D_00482E1C;
extern s16 D_00482E20;
extern s16 D_00482E24;
extern s32 D_00482E34;
}

extern "C" s32 RevelationBoardOpen_349220(s32 pad0, s32 arg1) {
    G *g;
    Obj *o;
    s32 v;
    s32 c;

    if (arg1 != 0) {
        D_00482E10 = 0;
        D_00482E14 = 1;
        D_00482E18 = 0;
        D_00482E1C = 0;
        D_00482E34 = SceneSoundGetSlot0HandleCur_207df0();
        RevelationBoardStateInit_34da10(D_0048238C, D_00482360);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x24F, 0, 1);
        D_0048238C->b7A2 = 0;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x47, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x47, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x187, 0.0f, D_0047D628, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x47, 1.0f, D_0047D634, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x47, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x4A, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x4A, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4A, 1.0f, D_0047D634, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x50, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x50, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x50, 1.0f, D_0047D634, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x50, -0x30, -0x30);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x49, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x49, 0.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x49, 0.0f, 0.0f, 0.0f, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x49, D_0047D638, D_0047D634, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x49, -0x30, -0x30);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x4F, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x4F, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4F, 1.0f, D_0047D634, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x4B, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x4B, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4B, 1.0f, D_0047D634, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x4B, -0x96, 0x153);
        g = GetGameData_1fede0();
        if (g == 0) {
            return 1;
        }
        o = PartyGetSlotChara_3c2fb0(g->w18, D_00482378->b6C);
        if (o == 0) {
            return 2;
        }
        RevelationBoardSetCharaPortrait_349660(o);
        v = o->v05C();
        D_0047F6C4 = v;
        c = o->wC;
        D_0047F6C0 = c;
        D_00482E20 = 0;
        RevelationBoardCursorUpdateMaybe_34d080(D_0048238C, c, v, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x52, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x51, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x52, 0.0f);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x51, 0.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x51, 0.0f, 0.0f, 0.0f, 0.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x52, 0x15A, 0x188);
        UiSetWidgetPos_290f60(D_00482360, 0x51, 0x15D, 0x18B);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5D, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x58, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x59, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xB5, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5A, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5D, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5C, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x5B, 0x1A, 0x1C);
        D_00482E20 = 0;
        D_00482E24 = 0;
    }
    StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
    return 1;
}
