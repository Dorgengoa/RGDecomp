#include "types.h"

typedef struct Ent {
    u8 pad0[4];
    s32 x4;
} Ent;

typedef struct Mdl {
    u8 pad0[4];
    s32 x4;
    u8 pad8[2];
    u16 lo : 2;
    u16 hi : 14;
} Mdl;

typedef struct Lst {
    u8 pad0[8];
    s32 x8;
} Lst;

typedef struct Cell {
    s16 x0;
    s16 x2;
    u8 pad4[0x1C];
} Cell;

typedef struct Img {
    u8 pad0[0x9C];
    s16 x9C;
} Img;

typedef struct Img28 {
    u8 pad0[4];
    s32 x4;
} Img28;

typedef struct Wnd {
    u8 pad0[0x20];
    void *x20;
    u8 pad24[4];
    Img28 *x28;
} Wnd;

typedef struct Txt {
    u8 pad0[0x1C];
    u16 x1C;
} Txt;

typedef struct Bit {
    u8 b0 : 1;
    u8 b1 : 7;
} Bit;

typedef struct E58 {
    u8 pad[0x58];
} E58;

typedef struct E9D0 {
    u8 pad[0x9D0];
} E9D0;

extern s32 LoadHandlesPollAllReady_28b000(s32, s32);
extern void InsectCageLoadFxModels_385390(s32, u8 *, s32, s32);
extern void MenuObjSoundInit_384590(s32 *);
extern s32 LoadHandleFindByName_28af30(s32, s32, s32);
extern s32 LoadHandleGetData_28b270(s32, s32);
extern s32 MsgTableLoadFromArchive_202a50(s32, char *, u8 *);
extern void TexGroupLoadFromArchive_202be0(s32, char *, u8 *, s32, s32);
extern s32 ArchiveGetFileData_181dd0(s32, char *, s32 *);
extern void InsectCageParamsLoad_386810(u8 *, s32, s32);
extern void InsectCageAdjTableParse_391720(u8 *, s32, s32, s32);
extern s32 GetMenuResGroup_206a40(void);
extern void ResGroupLoadByKind_42b840(s32, s32, s32, u8 *, s32);
extern Lst *MemStackNew_14e230(s32, u8 *);
extern void UiWidgetListReset_2912e0(Lst *);
extern void UiInitWidgetPool_290390(Lst *, u8 *, s32);
extern Ent *ResGroupListFindById_42c500(s32, s32);
extern void UiAddWidgets_2901d0(Lst *, s32, s32, s32);
extern void UiTextStyleReset_290450(Lst *);
extern Mdl *ResGroupListFindById_42c040(s32, s32);
extern void UiEntryListReset_28ec80(u8 *);
extern void UiEntryListAlloc_28e0c0(u8 *, u8 *, s32);
extern void UiEntryListLoad_28eb70(u8 *, s32, Lst *);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void LoadHandleArrayFree_28b0f0(s32, s32);
extern void MenuCursorObjClear_3862f0(u8 *);
extern s32 GetCursorObj_1fdb20(void);
extern void MenuCursorObjSetModel_386290(u8 *, s32);
extern void InsectCageItemIconReset_386070(u8 *);
extern void UiSetTextString_28f510(Lst *, s32, s32, s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern Wnd *UiFindWidget_290460(Lst *, s32);
extern void UiLayoutWindowFrame_28b8e0(void *, s32, s32, s32);
extern void *UiGetWidgetSprite_28fe10(Lst *, s32, s32);
extern void UiLayoutFrameRectsMaybe_28bbb0(void *, s32, s32);
extern s32 InsectCageMenuHasCage_391080(s32);
extern void UiSetSpriteSizeUvSize_28f670(Lst *, s32, s32, s32, s32, s32, s32);
extern s32 ScreenGetWidth_390d10(void);
extern void UiSetWidgetPos_290f60(Lst *, s32, s32, s32);
extern void *MenuResLookup_390960(s32);
extern void UiSetTextColor_290a40(Lst *, s32, s32, s32);
extern void UiSetTextPos_28f5d0(Lst *, s32, s32, s32, s32);
extern void UiSetTextFont_290a80(Lst *, s32, s32, s32);
extern void UiWindowFrameSetSize_388380(Txt *, s32, s32);
extern void UiSetWidgetTextColor_2907d0(Lst *, s32, s32, s32);
extern s32 MemStackAllocQw_14d950(u8 *, s32);
extern s32 MemStackAllocAligned64_14da10(u8 *, s32);
extern void MemStackInit_14d810(void *, s32, s32);
extern void MenuObjReset_387dc0(E9D0 *);
extern void MemStackClear_14dff0(u8 *);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 NameTableFindByName_159fb0(s32, char *, s32);
extern void InsectCageMenuResetAll_38b0d0(void);
extern void BitArray16Clear_384310(s32 *);
extern void UiEntryListResetRectByTag_28eb10(u8 *, s32);
extern s32 D_004802C4;
extern s32 D_004832A0;
extern E58 *D_004832A8;
extern E9D0 *D_004832AC;
extern s32 D_004832D8;
extern s32 D_004832E4;
extern s16 D_004832E8;
extern s32 D_00483300;
extern s32 D_00483304;
extern Lst *D_00483308;
extern Lst *D_0048330C;
extern s32 D_00483318;
extern s32 D_0048331C;
extern s32 D_0048335C;
extern s32 D_00483360;
extern u8 D_004833F8;
extern u16 D_0047FC08[4];
extern u16 D_00463E58[];
extern u16 D_00463E60[];
extern char D_00463F98[];
extern char D_00463FA8[];
extern char D_00463FB8[];
extern char D_00463FC8[];
extern char D_00463FD8[];
extern u8 D_004E9320[];
extern u8 D_004E9380[];
extern u8 D_004E93E0[];
extern u8 D_004E9440[];
extern u8 D_004E94C0[];
extern u8 D_004E94E0[];
extern s32 D_004E94F8[];
extern Bit D_004E9500[];
extern u8 D_004E9501[];
extern u8 D_004E9510[];
extern u8 D_004E9530[];

s32 InsectCageMenuLoadRes_38b280(void)
{
    s32 sz;
    u8 *heap;
    s32 pk;
    s32 p;
    s32 q;
    s32 w;
    s32 i;
    Ent *e;
    Mdl *m;
    s32 mv;
    s32 hv;
    s32 k;
    s32 id0;
    s32 id1;
    s32 id2;
    Wnd *o;
    Cell *c;
    Txt *t;

    if (LoadHandlesPollAllReady_28b000(D_004832E4, D_004832E8) == 0) {
        return 0;
    }
    heap = D_004E9320;
    InsectCageLoadFxModels_385390(D_004832D8, heap, D_004832E4, D_004832E8);
    MenuObjSoundInit_384590(&D_004832A0);
    p = LoadHandleFindByName_28af30(D_004802C4, D_004832E4, D_004832E8);
    pk = 0;
    if (p != 0) {
        pk = LoadHandleGetData_28b270(p, 0);
    }
    D_00483300 = MsgTableLoadFromArchive_202a50(pk, D_00463F98, heap);
    TexGroupLoadFromArchive_202be0(pk, D_00463FA8, heap, 0x262, 0);
    q = ArchiveGetFileData_181dd0(pk, D_00463FB8, &sz);
    if (q != 0) {
        InsectCageParamsLoad_386810(heap, q, sz);
        InsectCageAdjTableParse_391720(heap, q, sz, 0);
    }
    w = GetMenuResGroup_206a40();
    ResGroupLoadByKind_42b840(w, 2, 4, heap, pk);
    D_00483308 = MemStackNew_14e230(0x14, heap);
    UiWidgetListReset_2912e0(D_00483308);
    UiInitWidgetPool_290390(D_00483308, heap, 0x100);
    for (i = 0; i < 3; i++) {
        e = ResGroupListFindById_42c500(w, D_00463E58[i]);
        if (e != 0) {
            UiAddWidgets_2901d0(D_00483308, e->x4, 0, 0);
        }
    }
    D_00483308->x8 = -1;
    UiTextStyleReset_290450(D_00483308);
    D_0048330C = MemStackNew_14e230(0x14, heap);
    UiWidgetListReset_2912e0(D_0048330C);
    UiInitWidgetPool_290390(D_0048330C, heap, 10);
    e = ResGroupListFindById_42c500(w, 0x17);
    if (e != 0) {
        UiAddWidgets_2901d0(D_0048330C, e->x4, 0, 0);
    }
    D_0048330C->x8 = -1;
    UiTextStyleReset_290450(D_0048330C);
    m = ResGroupListFindById_42c040(w, 0xB);
    mv = m->x4;
    hv = m->hi;
    UiEntryListReset_28ec80(D_004E94E0);
    UiEntryListAlloc_28e0c0(D_004E94E0, heap, hv);
    UiEntryListLoad_28eb70(D_004E94E0, mv, D_00483308);
    D_004E94F8[0] = SceneSoundGetSlot0HandleCur_207df0();
    D_004E9500[0].b0 = 0;
    D_004E9501[0] = 0;
    LoadHandleArrayFree_28b0f0(D_004832E4, D_004832E8);
    MenuCursorObjClear_3862f0(D_004E94C0);
    MenuCursorObjSetModel_386290(D_004E94C0, GetCursorObj_1fdb20());
    InsectCageItemIconReset_386070(D_004E9510);
    InsectCageItemIconReset_386070(D_004E9530);
    for (i = 0; D_0047FC08[i] != 0; i++) {
        UiSetTextString_28f510(D_00483308, D_0047FC08[i], D_00483304 + (i << 9), 0);
    }
    UiSetTextString_28f510(D_00483308, 0x75F8, InsectCageMenuMsgLookup_389d30(0x50), 0);
    UiSetTextString_28f510(D_00483308, 0x75F8, InsectCageMenuMsgLookup_389d30(0x51), 1);
    for (k = 0; k < 3; k++) {
        id1 = (u16)(k + 0x7580);
        id0 = (u16)(k + 0x758A);
        id2 = (u16)(k + 0x7594);
        o = UiFindWidget_290460(D_00483308, id1);
        if (o != 0) {
            UiLayoutWindowFrame_28b8e0(o->x20, 0xA0, 0x8C, 5);
            for (c = (Cell *)o->x20; c->x0 != -1; c++) {
                c->x2 += 0x60;
            }
        }
        UiLayoutFrameRectsMaybe_28bbb0(UiGetWidgetSprite_28fe10(D_00483308, id2, 0), 0x6E, 0x62);
        if (InsectCageMenuHasCage_391080(k) == 1) {
            UiSetSpriteSizeUvSize_28f670(D_00483308, id2, 0, 0, 0, 0, 4);
        } else {
            UiSetSpriteSizeUvSize_28f670(D_00483308, id0, 0, 0, 0, 0, 0);
        }
        UiSetWidgetPos_290f60(D_00483308, id1, k * 0xA0 + (ScreenGetWidth_390d10() / 2 - 0xF0), 0x82);
    }
    o = UiFindWidget_290460(D_00483308, 0x75E4);
    if (o != 0) {
        ((Img *)o->x20)->x9C = 0;
        o->x28->x4 = D_00483304 + 0xE80;
    }
    o = UiFindWidget_290460(D_00483308, 0x7562);
    if (o != 0) {
        UiLayoutWindowFrame_28b8e0(o->x20, 0xA2, 0x9A, 6);
    }
    UiLayoutWindowFrame_28b8e0(MenuResLookup_390960(0x7558), 0xA2, 0x3C, 2);
    t = (Txt *)UiGetWidgetSprite_28fe10(D_00483308, 0x756C, 0);
    UiSetTextColor_290a40(D_00483308, 0x756C, 0xFF444444, 0);
    UiSetTextPos_28f5d0(D_00483308, 0x756C, 0xC, 0xF, 0);
    UiSetTextFont_290a80(D_00483308, 0x756C, 1, 0);
    if (t != 0) {
        t->x1C |= 0x200;
    }
    UiWindowFrameSetSize_388380(t, 0xA2, 0x24);
    for (i = 0; D_00463E60[i] != 0; i++) {
        UiSetWidgetTextColor_2907d0(D_00483308, D_00463E60[i], 0xFF444444, 1);
    }
    UiSetTextString_28f510(D_00483308, 0x7616, D_00483304 + 0xE00, 0);
    MemStackInit_14d810(D_004E93E0, MemStackAllocQw_14d950(heap, 0xF00), 0xF00);
    MemStackInit_14d810(D_004E9380, MemStackAllocAligned64_14da10(heap, 0x6400), 0x6400);
    for (i = 0; i < 5; i++) {
        MemStackInit_14d810(&D_004832A8[i], MemStackAllocAligned64_14da10(heap, 0x2A00), 0x2A00);
        MenuObjReset_387dc0(&D_004832AC[i]);
    }
    MemStackClear_14dff0(D_004E9440);
    MemStackInit_14d810(D_004E9440, MemStackAllocAligned64_14da10(heap, 0x1900), 0x1900);
    D_00483318 = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463FC8, 0x320);
    D_0048331C = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463FD8, 0x320);
    InsectCageMenuResetAll_38b0d0();
    BitArray16Clear_384310(&D_00483360);
    BitArray16Clear_384310(&D_0048335C);
    D_004833F8 = 0;
    UiEntryListResetRectByTag_28eb10(D_004E94E0, 0x7531);
    return 1;
}
