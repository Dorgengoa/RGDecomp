#include "types.h"

typedef struct S2aabe0 {
    u8 pad00[0x61];
    u8 m61;
    u8 pad62[0x16];
    s32 m78;
} S2aabe0;

typedef struct P2aabe0 {
    u8 pad00[0x2C];
    s32 m2C;
    s32 m30;
} P2aabe0;

typedef struct Q2aabe0 {
    u8 pad00[0xA];
    u8 b0 : 1;
} Q2aabe0;

typedef struct X2aabe0 {
    u8 pad00[0x18];
    void *m18;
} X2aabe0;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern S2aabe0 *D_00482384;
extern P2aabe0 *D_00482374;
extern const f32 D_0047D748 __attribute__((section(".sdata")));
extern f32 D_0047D74C;
extern u8 D_004B2570[];

extern void UiEntryListSelectByTag_28ea90(void *o, s32 a, s32 b);
extern void UiFadeWidgetAlpha_290690(void *o, s32 id, f32 a, f32 b, f32 c);
extern void *MenuGridCursorInput_28e170(void *o, void *n, s32 a, s32 b);
extern u8 MenuWeaponCombineUpdate_362920(void *o, void *t);
extern Q2aabe0 *MenuGetSelItem_2a02d0(void *o);
extern X2aabe0 *GetGameData_1fede0(void);
extern void InvClearNewFlagsMaybe_3c3490(void *a);
extern void MenuItemPageRefresh_2a03d0(void *o, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern s16 *UiEntryListFindByTag_28ea40(void *o, s32 id);
extern void MenuItemInfoWidgetsCache_2a65f0(void *v);
extern void MenuItemInfoPopupShow_2a33e0(void *o, void *a, s32 b, s32 c, void *d, s32 e,
                         s32 f, s32 g, f32 t);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 MenuWeaponCombineRunState_2aabe0(s32 unused, s32 en)
{
    u8 v[0x10];
    X2aabe0 *x;
    Q2aabe0 *h;
    s32 k;
    s16 *r;
    S2aabe0 *s;

    if (en != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
        s = D_00482384;
        s->m61 = 7;
        s->m78 = 0;
        UiFadeWidgetAlpha_290690(D_00482360, 0x137, 0.0f, D_0047D748, -1.0f);
    }
    if (MenuWeaponCombineUpdate_362920(D_00482384,
                     MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0)) == 3) {
        MenuGetSelItem_2a02d0(D_00482374)->b0 = 0;
        x = GetGameData_1fede0();
        InvClearNewFlagsMaybe_3c3490(x->m18);
        D_00482374->m2C = -1;
        D_00482374->m30 = -1;
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
        h = MenuGetSelItem_2a02d0(D_00482374);
        r = UiEntryListFindByTag_28ea40(D_00482364, 3);
        k = r[10] + r[11] * 8;
        MenuItemInfoWidgetsCache_2a65f0(v);
        MenuItemInfoPopupShow_2a33e0(D_00482374, h, 0x1AA, 0x1A9, v, 0x68, 0x15E, k, 2.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D74C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D74C, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
