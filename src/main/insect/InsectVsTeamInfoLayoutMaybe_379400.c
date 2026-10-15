#pragma optimization_level 3
#pragma opt_loop_invariants off
#include "types.h"

extern u8 *GetGameData_1fede0(void);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetSubItemGlyphUvW_28f0c0(s32, s32, s32, s32);
extern void UiSetSubItemX_28f1c0(s32, s32, s32, s32);
extern void UiSetSubItemPos_28f200(s32, s32, s32, s32, s32);
extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern void UiSetTextString_28f510(s32, u16, s32, s32);
extern void UiSetTextX_28f590(s32, s32, s32, s32);
extern void UiSetSpriteUvW_28f850(s32, s32, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
extern void InsectVsSetKindIconSpriteMaybe_37aab0(u8 *, s32);
extern void Sprintf_1343b8(void *, void *, u8);
extern s32 func_4F3320(void);
extern s32 D_004831D4;
extern s16 D_0047FAC8;
extern s16 D_0047FACA;
extern s16 D_0047FACC;
extern u8 D_004E9200[0x400];

typedef struct Ent {
    u8 pad0[0xD];
    u8 x0D;
    u8 pad1[0xA];
    u8 x18;
    u8 pad2;
    u16 x1A;
    u16 x1C;
    u16 x1E;
    u8 pad3;
    u8 x21;
    u8 x22;
    u8 pad4;
    u8 *x24;
} Ent;

typedef struct Obj {
    u8 pad0[0xF];
    s8 x0F;
    u8 pad1[8];
    Ent ent[5];
} Obj;

s32 InsectVsTeamInfoLayoutMaybe_379400(Obj *arg0, s32 arg1) {
    s16 tbl[3];
    s32 w;
    s32 m;
    s32 id;
    u16 win;
    s32 i;
    s32 msg;
    s32 h;
    Ent *base;
    s16 sel8;
    s32 sel;
    s32 col;
    s32 row;
    s32 n;
    s32 k;
    s32 v;
    Ent *e;
    u8 *p;
    u8 *s;
    s16 a;
    s16 bb;
    s32 aa;
    s32 a1;
    s32 b;

    w = D_004831D4;
    m = func_4F3320();
    id = *(s32 *)(*(u8 **)(*(u8 **)(GetGameData_1fede0() + 0x24) + 0x1188) + 8);
    aa = (s16)arg1;
    if (aa == 2) {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(m, 0x5E1), 0);
    } else if (id == 0x25C || id == 0x267 || id == 0x26F || id == 0x25D || aa == 1) {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, 0, 0);
    } else {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(m, 0x5DF), 0);
    }
    UiSetTextString_28f510(w, win, MsgTableLookup_28aa30(m, 0x5E0), 1);
    if (arg0 == NULL) {
        return -1;
    }
    base = arg0->ent;
    if (base == NULL) {
        return -1;
    }
    sel8 = arg0->x0F;
    UiSetSpriteX_28fcd0(w, 0x9CA8, 0x13C, 0x28);
    n = 0;
    for (i = 0; i < 0xF; i++) {
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 0x14; i++) {
        UiSetTextString_28f510(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 5; i++) {
        UiSetSpriteW_28fbf0(w, 0x9CA9, 0, i);
        UiSetSpriteUvW_28f850(w, 0x9CA9, 0, i);
    }
    UiSetSubItemX_28f1c0(w, 0x9CA8, 0x35, 0xF);
    UiSetSpriteX_28fcd0(w, 0x9CA8, 0x24, 0x25);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x460), 0x12);
    msg = 0x514;
    if (id == 0x12F || id == 0x192 || id == 0x1F6) {
        msg = 0x514;
    } else if (id == 0x130 || id == 0x193 || id == 0x1F7) {
        msg = 0x515;
    } else if (id == 0x25C || id == 0x267 || id == 0x26F || id == 0x25D) {
        msg = 0x17;
    }
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, msg), 0);
    h = UiGetWidgetTextWidth_28f400(w, 0x9CA8, 0);
    UiSetTextX_28f590(w, 0x9CA8, 0x100 - h / 2, 0);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x456), 2);
    UiSetTextX_28f590(w, 0x9CA8, 0x140, 2);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x44C), 1);
    UiSetTextString_28f510(w, 0x9CA8, (s32)arg0, 0x13);
    for (id = 0; id < 3; id++) {
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, id + 0xF);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, id + 0xF);
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, id + 0x21);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, id + 0x21);
    }
    tbl[0] = D_0047FAC8;
    tbl[1] = D_0047FACA;
    tbl[2] = D_0047FACC;
    for (id = 0; id < 3; id++) {
        v = *(s16 *)((u32)&tbl[(u32)id]);
        UiSetSpriteW_28fbf0(w, 0x9CA8, v, id + 0xF);
        UiSetSpriteUvW_28f850(w, 0x9CA8, v, id + 0xF);
        p = UiGetWidgetSprite_28fe10(w, 0x9CA8, id + 0xF);
        *(s32 *)(p + 0x14) = 0x40400000;
        v = *(s16 *)((u32)&tbl[id]);
        UiSetSpriteW_28fbf0(w, 0x9CA8, v, id + 0x21);
        UiSetSpriteUvW_28f850(w, 0x9CA8, v, id + 0x21);
        p = UiGetWidgetSprite_28fe10(w, 0x9CA8, id + 0x21);
        *(s32 *)(p + 0x14) = 0x40000000;
    }
    sel = sel8;
    k = 0;
    i = 0;
    col = sel % 2;
    row = sel / 2;
    do {
        InsectVsSetKindIconSpriteMaybe_37aab0(UiGetWidgetSprite_28fe10(w, 0x9CA9, n), (e = &base[(u32)(s32)i])->x0D);
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, n);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, n, e->x1A);
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, n + 5);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, n + 5, e->x1C);
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, n + 0xA);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, n + 0xA, e->x1E);
        p = &e->x18;
        s = D_004E9200 + n * 8;
        Sprintf_1343b8(s, (void *)MsgTableLookup_28aa30(m, 0x3F2), *p);
        UiSetTextString_28f510(w, 0x9CA8, (s32)s, n + 0xD);
        if (*p >= 6) {
            UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x3FC), n + 0xD);
        }
        e = &base[(u32)i];
        UiSetTextString_28f510(w, 0x9CA8, (s32)e, n + 3);
        UiSetTextString_28f510(w, 0x9CA8, *(s32 *)(e->x24 + 0xC), n + 8);
        if (i == sel) {
            v = (s16)row;
            UiSetSpritePos_28fd10(w, 0x9CA8, (s16)col * 0xE6 + 0x24, v * 0x68 + 0x54, 0x27);
            UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0, i + 0xF);
            e = &base[(s32)i];
            UiSetSpritePos_28fd10(w, 0x9CA8, e->x21 * 32 + 0x11F, e->x22 * 33 + 0x149, 0x2E);
        } else {
            UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, i + 0xF);
            e = &base[i];
            a = e->x21;
            bb = e->x22;
            UiSetSpritePos_28fd10(w, 0x9CA8, a * 32 + 0x11F, bb * 33 + 0x149, k + 0x2F);
            UiSetSubItemPos_28f200(w, 0x9CA8, a * 32 + 0x130, bb * 33 + 0x14F, k + 0x14);
            UiSetWidgetSubItemValue_291250(w, 0x9CA8, k + 0x14, i + 1);
            k++;
        }
        i++;
        n++;
    } while (i < 5);
    return 5;
}
