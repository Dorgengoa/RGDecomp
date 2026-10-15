#include "types.h"

typedef struct Wnd { s32 pad[7]; s32 f1C; } Wnd;
typedef struct Item { Wnd *w; s32 pad4; s32 pad8; s16 padC; s16 fE; s32 pad10; s16 pad14; s16 f16; } Item;
typedef struct Save { u8 pad[0x9C4]; s32 f9C4; s32 f9C8; } Save;
typedef struct Obj { u8 pad[0x12]; s16 f12; } Obj;

extern "C" {
extern Item *UiEntryListFindByTag_28ea40(void *, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetTextColor_2907d0(s32, s32, s32, s32);
extern void UiSetTextColor_290a40(s32, s32, s32, s32);
extern void UiSetWidgetSprites_290b90(s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuObjSetPauseFx_384b20(s32);
extern void InsectCagePreviewModelSetup_389370(s32, s32);
extern void InsectCageMenuSetCursorTarget_389790(s32, Obj *, s32);
extern void InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
extern void InsectCageMenuSetCursorVisible_389d00(s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 MenuResLookup_390960(s32);
extern void InsectCageMenuSetDrawFlag_390a80(s32, s32);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern s32 GetMenuWidgetRoot_390d70(void);
extern s32 MenuObjCountActive_390ec0(void);
extern Save *InsectCageMenuGetCursorObj_390f70(void);
extern char *strcpy(char *, const char *);
extern s8 D_0047FBE8[2];
extern s32 D_004832D8;
extern char *D_00483304;
extern s16 D_00483334;
extern u8 D_004E94E0[0x400];
}
static inline s32 IsSet(s32 x) { return x != 0; }

extern "C" s32 InsectCageMenuTopOpen_38ffa0(Obj *arg0, s32 arg1) {
    s32 i;
    s32 w;
    Item *item;
    Save *sv;

    InsectCageMenuSetStateFlagMaybe_390aa0(1, 1);
    InsectCageMenuSetStateFlagMaybe_390aa0(2, 1);
    MenuObjSetPauseFx_384b20(D_004832D8);
    for (i = 0; i < 3; i++) {
        InsectCageMenuSetRowMarker_389a80(0, 0, i, -1);
        InsectCageMenuSetRowMarker_389a80(1, 0, i, -1);
    }
    UiSetWidgetVisible_290010(arg1, 0x7562, 1, -1);
    InsectCageMenuSetDrawFlag_390a80(2, 0);
    InsectCageMenuSetDrawFlag_390a80(7, 0);
    InsectCageMenuSetStateFlagMaybe_390aa0(7, 0);
    UiSetWidgetsVisibleById_291110(arg1, 0x753A, 1, 1);
    UiSetWidgetsVisibleById_291110(arg1, 0x7616, 0, 1);
    InsectCagePreviewModelSetup_389370(0, 1);
    w = GetMenuWidgetRoot_390d70();
    if (w != 0) {
        UiSetWidgetAlpha_2907a0(w, 0x227, 0.0f);
    }
    item = UiEntryListFindByTag_28ea40(D_004E94E0, 0x7532);
    item->w->f1C |= 1;
    item->fE = 5;
    D_00483334 = 4;
    UiSetWidgetTextColor_2907d0(arg1, 0x7562, 0xFF444444, 1);
    InsectCageMenuSetCursorVisible_389d00(1);
    for (i = 0; i < 6; i++) {
        UiSetTextString_28f510(arg1, 0x7562, InsectCageMenuMsgLookup_389d30(i + 0x14), i);
    }
    UiSetWidgetSprites_290b90(arg1, 0x7562, MenuResLookup_390960(0x754E));
    if (MenuObjCountActive_390ec0() <= 0) {
        arg0->f12 = 3;
        item->w->f1C &= ~1;
        UiSetWidgetTextColor_2907d0(arg1, 0x7562, 0xFF202020, 1);
        UiSetTextColor_290a40(arg1, 0x7562, 0xFF444444, 3);
        UiSetWidgetsVisibleById_291110(arg1, 0x7544, 0, 1);
    } else {
        UiSetWidgetsVisibleById_291110(arg1, 0x7544, 1, 1);
        sv = InsectCageMenuGetCursorObj_390f70();
        if (IsSet(sv->f9C4) || IsSet(sv->f9C8)) {
            item->f16 = 0;
            item->fE = 1;
            UiSetWidgetSprites_290b90(arg1, 0x7562, MenuResLookup_390960(0x7558));
            if (IsSet(sv->f9C4)) {
                strcpy(D_00483304 + 0x600, (char *)InsectCageMenuMsgLookup_389d30(0x32));
            }
            if (IsSet(sv->f9C8)) {
                strcpy(D_00483304 + 0x600, (char *)InsectCageMenuMsgLookup_389d30(0x33));
            }
            UiSetWidgetsVisibleById_291110(arg1, 0x756C, 1, 1);
            for (i = 0; i < 2; i++) {
                UiSetTextString_28f510(arg1, 0x7562, InsectCageMenuMsgLookup_389d30(D_0047FBE8[i] + 0x14), i);
            }
            for (i = 2; i < 5; i++) {
                UiSetTextString_28f510(arg1, 0x7562, 0, i);
            }
        }
    }
    InsectCageMenuSetCursorTarget_389790(0, arg0, 1);
    return 1;
}
