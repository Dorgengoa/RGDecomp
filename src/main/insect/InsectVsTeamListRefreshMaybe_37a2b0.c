#include "types.h"

typedef struct Sub20 {
    u8 pad0[0x60];
    s16 h60;            /* +0x60 */
    u8 pad62[0x1E];
    s16 h80;            /* +0x80 */
} Sub20;

typedef struct Widget {
    u8 pad0[0x20];
    Sub20 *x20;         /* +0x20 */
} Widget;

typedef struct Ent {
    u8 pad0[0xD];
    u8 bD;              /* +0x0D */
    u8 padE[0xA];
    u8 b18;             /* +0x18 */
    u8 pad19[0xF];
} Ent;

typedef struct Flags {
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 4;
} Flags;

typedef struct Rec {
    char name[0xF];
    s8 sF;              /* +0x0F */
    Flags fl;           /* +0x10 */
    u8 pad11[7];
    Ent ents[5];        /* +0x18 */
} Rec;

typedef struct Kind {
    u8 pad0[8];
    s32 x8;
} Kind;

typedef struct Actor24 {
    u8 pad0[8];
    Rec recs[1];        /* +0x08 */
} Actor24;

typedef struct Actor {
    u8 pad0[0x24];
    u8 *x24;            /* +0x24 */
} Actor;

extern Actor *GetGameData_1fede0(void);
extern s32 func_4F3320(void);
extern char *MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextString_28f510(s32, u16, char *, s32);
extern s32 UiGetWidgetTextWidth_28f400(s32, u16, s32);
extern void UiSetTextX_28f590(s32, u16, s32, s32);
extern void UiSetTextY_28f550(s32, u16, s32, s32);
extern Widget *UiFindWidget_290460(s32, u16);
extern void UiSetWidgetsVisibleById_291110(s32, u16, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, u16, u16);
extern void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
extern void UiSetSpriteX_28fcd0(s32, u16, s32, s32);
extern void UiSetSubItemX_28f1c0(s32, u16, s32, s16);
extern void UiSetWidgetSubItemValue_291250(s32, u16, s16, s64);
extern void UiSetWidgetTextColor_2907d0(s32, u16, u32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, u16, s32);
extern void InsectVsSetKindIconSpriteMaybe_37aab0(s32, u8);
extern void Sprintf_1343b8(char *, char *, u8);
extern char *strcpy(char *, const char *);
extern u16 D_00463A80[];
extern u16 D_00463A82[];
extern u16 D_00463A84[];
extern u16 D_00463A86[];
extern s32 D_004831D4;
extern s16 D_004831E8[3];
extern char D_004E9120[3][5][8];
extern char D_004E91A0[3][16];

#pragma optimization_level 3
#pragma opt_loop_invariants off
void InsectVsTeamListRefreshMaybe_37a2b0(s32 arg0)
{
    Actor *actor;
    s32 msg;
    s32 w;
    Rec *recs;
    u16 *tbl;
    s32 kind;
    s16 k;
    s32 n;
    s32 i;
    s32 j;
    u32 t0;
    u32 t1;
    u32 t2;
    u32 t3;
    s32 no;
    u16 id;
    s32 id2;
    u16 id0;
    u16 id1;
    u16 idCE;
    s32 e;
    u16 idE0;
    s32 base;
    Widget *o;
    Flags *pf;
    u16 idB;
    char *dst;
    Ent *ents;
    s32 ia;
    s32 ib;
    char (*names)[8];
    s32 cnt;
    s32 m;
    Rec *rec;
    Ent *ent;
    u8 *pl;
    u16 idD;
    char *nm;
    f32 f;
    u32 col;

    actor = GetGameData_1fede0();
    if (actor == 0) {
        return;
    }
    msg = func_4F3320();
    w = D_004831D4;
    recs = (Rec *)(actor->x24 + 8);
    tbl = D_00463A80;
    kind = (*(Kind **)(actor->x24 + 0x1188))->x8;
    k = 0x3E8;
    if (kind == 0x25A || kind == 0x264 || kind == 0x26F) {
        k = 0x17;
    } else if (kind == 0x278) {
        k = 0x22;
    }
    UiSetTextString_28f510(w, 0x9CAA, MsgTableLookup_28aa30(msg, k), 0);
    n = UiGetWidgetTextWidth_28f400(w, 0x9CAA, 0);
    UiSetTextX_28f590(w, 0x9CAA, 0x100 - n / 2, 0);
    UiSetTextY_28f550(w, 0x9CAA, 0x1E, 0);
    i = 0;
    t0 = D_00463A80[0];
    t1 = D_00463A82[0];
    t2 = D_00463A84[0];
    t3 = D_00463A86[0];
    for (; i < 3; i++) {
        id = i * 20;
        no = arg0 + i;
        D_004831E8[i] = 0;
        idCE = id + 0x7FFF + 0x8CE;
        e = id + 0x7FFF + 0x8CD;
        idE0 = e;
        o = UiFindWidget_290460(w, id + 0x7FFF + 0x8CF);
        if (o != 0) {
            if (o->x20 != 0) {
                o->x20->h60 = 0x26;
                o->x20->h80 = -1;
            }
        }
        id2 = (u16)(s32)id;
        for (j = 0; tbl[j] != 0xFFFF; j++) {
            id1 = id + tbl[j]; if (j == 1) id1 = id2 + tbl[j];
            UiSetWidgetsVisibleById_291110(w, id1, 0, 1);
            UiSetWidgetParent_2911a0(w, id1, idE0);
            UiSetWidgetColor_2905b0(w, idE0, 1.0f, 1.0f, 1.0f, -1.0f);
        }
        base = id + 0x7FFF + 0x8D7;
        for (j = 0; j < 3; j++) {
            UiSetWidgetsVisibleById_291110(w, base + j, 0, 1);
        }
        id0 = (u16)(s32)id;
        UiSetWidgetsVisibleById_291110(w, id0 + 0x7FFF + 0x8D6, 0, 1);
        UiSetWidgetsVisibleById_291110(w, id0 + 0x7FFF + 0x8D3, 0, 1);
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1CAC, 0, 1);
        UiSetSpriteX_28fcd0(w, idCE, -1, 0);
        UiSetSubItemX_28f1c0(w, idCE, 0x21, 0);
        UiSetWidgetSubItemValue_291250(w, idCE, 0, no + 1);
        m = (u32)i * 20;
        UiSetWidgetsVisibleById_291110(w, t0 + m, 0, 1);
        UiSetWidgetsVisibleById_291110(w, t1 + m, 0, 1);
        UiSetWidgetsVisibleById_291110(w, t2 + m, 0, 1);
        UiSetWidgetsVisibleById_291110(w, t3 + m, 0, 1);
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1C9B, 0, 1);
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1CA5, 0, 1);
        if (recs == 0) {
            continue;
        }
        rec = &recs[no];
        pf = &rec->fl;
        if (rec->fl.f0 && !rec->fl.f3) {
            UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1CA5, 1, 1);
            idB = i + 0x7FFF + 0x1C9B;
            UiSetWidgetsVisibleById_291110(w, idB, 1, 1);
            nm = recs[(u32)no].name;
            dst = D_004E91A0[i];
            strcpy(dst, nm);
            UiSetTextString_28f510(w, idB, dst, 0);
            UiSetTextString_28f510(w, idB, MsgTableLookup_28aa30(msg, 0x3E9), 1);
        rec = (Rec *)(u32)rec;
            ents = rec->ents;
            cnt = 0;
            m = 0;
            ia = i + 0x7FFF + 0x1CA5;
            ib = i + 0x7FFF + 0x1C9B;
            names = D_004E9120[i];
            do {
                {
                    s32 h = UiGetWidgetSprite_28fe10(w, ia, m);
                    ent = &ents[m];
                    InsectVsSetKindIconSpriteMaybe_37aab0(h, ent->bD);
                }
                pl = &ent->b18;
                idD = ib;
                nm = names[m];
                Sprintf_1343b8(nm, MsgTableLookup_28aa30(msg, 0x3F2), *pl);
                UiSetTextString_28f510(w, idD, nm, m + 2);
                if (*pl >= 6) {
                    UiSetTextString_28f510(w, idD, MsgTableLookup_28aa30(msg, 0x3FC), m + 2);
                }
                if (m != rec->sF) {
                    UiSetSubItemX_28f1c0(w, idD, m * 0x4F + 0x2C, cnt);
                    UiSetWidgetSubItemValue_291250(w, idD, cnt, m + 1);
                    cnt = (s16)(cnt + 1);
                }
                m++;
            } while (m < 5);
            UiSetSpriteX_28fcd0(w, i + 0x7FFF + 0x1C9B, ((Rec *)((u32)(s32)no * 0xE0 + (u32)recs))->sF * 0x4F + 0x1B, 2);
            f = 1.0f;
            col = 0xFF303030;
            if (pf->f3) {
                f = 0.5f;
                col = 0xFF202020;
            }
            UiSetWidgetTextColor_2907d0(w, i + 0x7FFF + 0x1C9B, col, 1);
            UiSetWidgetColor_2905b0(w, e, f, f, f, -1.0f);
        } else {
            UiSetWidgetColor_2905b0(w, e, 1.0f, 1.0f, 1.0f, -1.0f);
            UiSetWidgetTextColor_2907d0(w, i + 0x7FFF + 0x1C9B, 0xFF303030, 1);
        }
    }
}
