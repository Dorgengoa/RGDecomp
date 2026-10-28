/* rgp:protos */
#line 1
#include "types.h"

class VTbl {
public:
    VC_VPTR_MEMBER;     
         
         
         
     
    u8 * get(s16 a0) { return VCM(u8 *, (void *, s16), 0x70, a0); } /* 0x70 */
};

typedef struct Nm {
    u8 pad0[0xC];
    char *xC;
} Nm;

typedef struct Ent {
    char name[0xD];
    u8 xD;
    u8 padE[0x18 - 0xE];
    u8 x18;
    u8 pad19;
    u16 x1A;
    u16 x1C;
    u16 x1E;
    u8 pad20[3];
    u8 x23;
    Nm *x24;
} Ent;

typedef struct Spr {
    u8 pad0[0x14];
    f32 x14;
} Spr;

typedef struct M40 {
    u8 pad0[8];
    VTbl *x8;
} M40;

typedef struct M8 {
    u8 pad0[0x40];
    M40 *x40;
} M8;

typedef struct B1188 {
    u8 pad0[8];
    s32 x8;
} B1188;

typedef struct B24 {
    u8 pad0[0x1188];
    B1188 *x1188;
} B24;

typedef struct Gm {
    u8 pad0[8];
    M8 *x8;
    u8 padC[0x24 - 0xC];
    B24 *x24;
} Gm;

extern "C" {
void Sprintf_1343b8(char *, char *, s32);
Gm *GetGameData_1fede0(void);
char *MsgTableLookup_28aa30(s32, s32);
void UiSetSubItemGlyphUvW_28f0c0(s32, s32, s32, s32);
void UiSetSubItemX_28f1c0(s32, s32, s32, s32);
s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, char *, s32);
void UiSetTextX_28f590(s32, s32, s32, s32);
void UiSetSpriteUvW_28f850(s32, s32, s32, s32);
void UiSetSpriteW_28fbf0(s32, s32, s32, s32);
void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
Spr *UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetSubItemValue_291250(s32, s32, s32, long long);
void InsectVsSetKindIconSpriteMaybe_37aab0(Spr *, s32);
s32 func_4F3320(void);
extern s16 D_0047FAC0;
extern s16 D_0047FAC2;
extern s16 D_0047FAC4;
extern s32 D_004831D4;
extern char D_004E91D0[];
s16 InsectVsCagePanelFillMaybe_379be0(Ent *list, s32 cat, s32 n, s32 clr);
}

#pragma push
#pragma optimization_level 3
extern "C" s16 InsectVsCagePanelFillMaybe_379be0(Ent *list, s32 cat, s32 n, s32 clr)
{
    s16 idx[6];
    s16 tbl[3];
    s16 count;
    s16 c;
    s32 v2;
    char *buf;
    s32 cnt;
    Spr *o;
    Gm *gm;
    s32 w;
    s32 t;
    Ent *e;
    s32 v;
    s32 msg;
    s32 k;
    s32 id;
    s32 j;
    s32 i;
    u8 *pl;

    count = 0;
    w = D_004831D4;
    msg = func_4F3320();
    UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(msg, 0x5DF), 0);
    UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(msg, 0x5E0), 1);
    if (clr) {
        UiSetTextString_28f510(w, 0x9CA7, 0, 0);
    }
    if (list == 0) {
        return -1;
    }
    for (i = 0; i < 6; i++) {
        idx[i] = -1;
    }
    c = cat;
    for (i = 0; i < (s16)n; i++) {
        if (c == list[i].x23) {
            idx[count++] = i;
        }
    }
    UiSetSpriteX_28fcd0(w, 0x9CA8, -1, 0x28);
    UiSetTextString_28f510(w, 0x9CA8, 0, 0x12);
    j = 0;
    for (i = 0; i < 15; i++) {
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 20; i++) {
        UiSetTextString_28f510(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 5; i++) {
        UiSetSpriteW_28fbf0(w, 0x9CA9, 0, i);
        UiSetSpriteUvW_28f850(w, 0x9CA9, 0, i);
    }
    UiSetSubItemX_28f1c0(w, 0x9CA8, -1, 0xF);
    UiSetSpriteX_28fcd0(w, 0x9CA8, -1, 0x25);
    id = 0x514;
    gm = GetGameData_1fede0();
    t = gm->x24->x1188->x8;
    if (t == 0x12F || t == 0x192 || t == 0x1F6) {
        id = 0x514;
    } else if (t == 0x130 || t == 0x193 || t == 0x1F7) {
        id = 0x515;
    } else if (t == 0x25C || t == 0x267 || t == 0x26F || t == 0x25D) {
        id = 0x17;
    }
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(msg, id), 0);
    UiSetTextX_28f590(w, 0x9CA8, 0x100 - UiGetWidgetTextWidth_28f400(w, 0x9CA8, 0) / 2, 0);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(msg, 0x4BA), 2);
    UiSetTextX_28f590(w, 0x9CA8, 0x102, 2);
    UiSetTextString_28f510(w, 0x9CA8, ((Nm *)gm->x8->x40->x8->get((s16)(c + 0x4167)))->xC, 1);
    for (i = 0; i < 3; i++) {
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, i + 0xF);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, i + 0xF);
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, i + 0x21);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, i + 0x21);
    }
    c = count;
    if (c == 0) {
        return 0;
    }
    tbl[0] = D_0047FAC0;
    tbl[1] = D_0047FAC2;
    tbl[2] = D_0047FAC4;
    for (i = 0; i < 3; i++) {
        v = tbl[i];
        UiSetSpriteW_28fbf0(w, 0x9CA8, v, i + 0xF);
        UiSetSpriteUvW_28f850(w, 0x9CA8, v, i + 0xF);
        o = UiGetWidgetSprite_28fe10(w, 0x9CA8, i + 0xF);
        if (c == 5) {
            o->x14 = 3.0f;
        } else if (c > 2) {
            o->x14 = 2.0f;
        } else {
            o->x14 = 0.0f;
        }
        UiSetSpriteW_28fbf0(w, 0x9CA8, tbl[i], i + 0x21);
        UiSetSpriteUvW_28f850(w, 0x9CA8, tbl[i], i + 0x21);
        o = UiGetWidgetSprite_28fe10(w, 0x9CA8, i + 0x21);
        if (c > 3) {
            o->x14 = 2.0f;
        } else if (c >= 2) {
            o->x14 = 0.0f;
        } else {
            UiSetSpriteW_28fbf0(w, 0x9CA8, 0, i + 0x21);
            UiSetSpriteUvW_28f850(w, 0x9CA8, 0, i + 0x21);
        }
    }
    for (; (k = *(s16 *)((s32)&idx[j])) != -1; j++) {
        o = UiGetWidgetSprite_28fe10(w, 0x9CA9, j);
        InsectVsSetKindIconSpriteMaybe_37aab0(o, list[k].xD);
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, j);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, j, (long long)(list[k].x1A));
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, j + 5);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, j + 5, (long long)(list[k].x1C));
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0xC, j + 10);
        UiSetWidgetSubItemValue_291250(w, 0x9CA8, j + 10, (long long)(list[k].x1E));
        pl = &list[k].x18;
        buf = D_004E91D0 + j * 8;
        Sprintf_1343b8(buf, MsgTableLookup_28aa30(msg, 0x3F2), *pl);
        UiSetTextString_28f510(w, 0x9CA8, buf, j + 0xD);
        if (!(*pl < 6)) {
            UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(msg, 0x3FC), j + 0xD);
        }
        e = (Ent *)((u8 *)list + k * sizeof(Ent));
        UiSetTextString_28f510(w, 0x9CA8, e->name, j + 3);
        UiSetTextString_28f510(w, 0x9CA8, e->x24->xC, j + 8);
    }
    return count;
}
#pragma pop
