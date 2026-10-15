#include "types.h"
#pragma divbyzerocheck on

typedef struct Sub20 {
    u8 pad0[0x60];
    s16 h60;            /* +0x60 */
} Sub20;

typedef struct Cell {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x10];
} Cell;

typedef struct Sub28 {
    s16 h0;             /* +0x00 */
    s16 h2;             /* +0x02 */
    u8 pad4[6];
    u8 bA;              /* +0x0A */
    u8 padb;
    u32 xC;             /* +0x0C */
} Sub28;

typedef struct Sub24 {
    u8 pad0[8];
    s64 x8;             /* +0x08 */
    s16 h10;            /* +0x10 */
    u8 pad12[0x16];
    s64 x28;            /* +0x28 */
    u8 pad30[0x18];
    s64 x48;            /* +0x48 */
} Sub24;

typedef struct Widget {
    u8 pad0[0x20];
    void *x20;          /* +0x20 */
    void *x24;          /* +0x24 */
    Sub28 *x28;         /* +0x28 */
} Widget;

typedef struct Buf16 {
    char c[16];
} Buf16;

extern s32 GetGameData_1fede0(void);
extern void UiSetWidgetsVisibleById_291110(s32, u16, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, u16, u16);
extern Widget *UiFindWidget_290460(s32, u16);
extern void UiSetWidgetSubItemValue_291250(s32, u16, s32, s64);
extern void *memset(void *, s32, u32);
extern void UiSetTextString_28f510(s32, u16, char *, s32);
extern u8 *SlotRecordFindById_3e4e80(s32, s32);
extern s32 SaveSlotEntryIsValidAt_373440(s32, s32);
extern s32 SaveSlotEntryIsEmptyAt_3734c0(s32, s32);
extern s32 SaveSlotEntryIsNoSpaceAt_373480(s32, s32);
extern void UiSetWidgetPos_290f60(s32, u16, s32, s32);
extern void UiSetSpriteUv_28f970(s32, u16, u8, u8, s32);
extern char *strcpy(char *, const char *);
extern void SavePlayTimeSplit_3eebf0(u8 *, s32 *, s32 *, s32 *, s32 *);
extern char *SaveMenuMsgLookup_376b30(s32);
extern void UiSetTextCenteredX_28f300(s32, u16, s32, s32);
extern void UiSetWidgetTexName_290ac0(s32, u16, char *);
extern void UiSetWidgetAlpha_2907a0(s32, u16, f32);
extern void UiSetSpritePosSizeUv_28f710(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u16 D_00463AA0[][10];
extern u16 D_00463AC8[][3];
extern u16 D_00463ACA[][3];
extern u16 D_00463ACC[][3];
extern u16 D_00463AD8[];
extern u16 D_00463AE0[];
extern u16 D_00463AE8[];
extern u16 D_00463AF0[];
extern u16 D_00463AF8[];
extern const s8 D_00463A40[10][3];
extern u8 D_0047FAD0[4][2];
extern char D_0047FAE0[16] __attribute__((section(".sdata")));
extern f32 D_0047D1E8;
extern s32 D_004831D0;
extern s32 D_004831D4;
extern s16 D_004831E8[3];
extern char *D_004831F8;

#pragma optimization_level 3
#pragma opt_dead_assignments off
void SaveSlotListRefreshDetailMaybe_3783c0(s32 arg0, s32 sel)
{
  s32 w_w55;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    char buf[16];
    s32 actor;
    s32 w;
    u16 *tbl;
    s32 j;
  s32 j_w190;
    s16 *p16;
    u32 m1;
    u32 m2;
    u32 m3;
    u32 t3;
    u32 ta;
    u32 tb;
    u32 tc;
    u32 td;
    u16 *te;
    u16 id;
    u16 id2;
    u16 id3;
    u16 idA;
    u16 idB;
    u16 idC;
    u16 idX;
    u16 idY;
    u16 id1;
    u16 id0;
    u16 id5;
    u16 idD;
    s32 no;
    Widget *s1;
    Widget *s0;
    Widget *o;
    u8 *ch;
    s32 x;
    s32 k;
    s32 q;
    s32 r;
    s32 n;
    s32 v;
    s32 cc;
    Sub24 *q2;
    Cell *cell;
    char *str;

    actor = GetGameData_1fede0();
    if (actor == 0) {
        return;
    }
    tbl = D_00463AA0[sel];
    w_w55 = D_004831D4;
    m1 = D_00463AC8[sel][0];
    m2 = D_00463ACA[sel][0];
    m3 = D_00463ACC[sel][0];
    i = 0;
    ta = D_00463AD8[sel];
    tb = D_00463AE0[sel];
    tc = D_00463AE8[sel];
    td = D_00463AF0[sel];
    for (; i < 3; i++) {
        id = m1 * i;
        j = 0;
        id2 = m2 * i;
        p16 = &D_004831E8[i];
        *p16 = 0;
        t3 = m3 * i;
        idA = id + ta;
        idB = id + tb;
        idC = id + tc;
        id3 = t3;
        for (; tbl[j] != 0xFFFF; j++) {
            id1 = id + tbl[j];
            if ((u32)(j - 5) < 2) {
                id1 = id2 + tbl[j];
            } else if (j == 1) {
                id1 = id3 + tbl[j];
            }
            UiSetWidgetsVisibleById_291110(w_w55, id1, 0, 1);
            UiSetWidgetParent_2911a0(w_w55, id1, idC);
        }
        id0 = (u16)(s32)id;
        idD = id0 + td;
        UiSetWidgetsVisibleById_291110(w_w55, idD, 0, 1);
        no = arg0 + i;
        id5 = tbl[2] + id0;
        s1 = UiFindWidget_290460(w_w55, id5);
        idY = tbl[3] + id0;
        idX = tbl[8] + id0;
        UiSetWidgetSubItemValue_291250(w_w55, idA, 0, no + 1);
        s0 = UiFindWidget_290460(w_w55, idB);
        if (D_004831F8 != 0) {
            k = i << 8;
            memset(D_004831F8 + k, 0, 0x100);
            UiSetTextString_28f510(w_w55, id5, D_004831F8 + k, 0);
            UiSetTextString_28f510(w_w55, idY, D_004831F8 + k + 0x80, 0);
        }
        ch = SlotRecordFindById_3e4e80(actor, no);
        if (SaveSlotEntryIsValidAt_373440(D_004831D0, no) != 0) {
            o = UiFindWidget_290460(w_w55, idB);
            if (o != 0) {
                if (o->x20 != 0) {
                    ((Sub20 *)o->x20)->h60 = 0x6C;
                }
            }
            for (j = 0; tbl[j] != 0xFFFF; j++) {
                id1 = id + tbl[j];
                if ((u32)(j - 5) < 2) {
                    id1 = id2 + tbl[j];
                } else if (j == 1) {
                    id1 = id3 + tbl[j];
                }
                UiSetWidgetParent_2911a0(w_w55, id1, idC);
                UiSetWidgetsVisibleById_291110(w_w55, id1, 1, 1);
            }
            x = 0;
            UiSetWidgetPos_290f60(w_w55, idX, 0x53, 6);
            k = *(s16 *)(ch + 0x294);
            if (k > 0) {
                k = k - 1;
                x = 1;
                if (k < 0) {
                    k = 0;
                }
                if (k > 3) {
                    k = 3;
                }
                UiSetSpriteUv_28f970(w_w55, idX, D_0047FAD0[k][0], D_0047FAD0[k][1], 0);
            }
            UiSetWidgetsVisibleById_291110(w_w55, idX, x, 1);
            *p16 = *(u16 *)(ch + 0x338);
            if (D_004831F8 != 0) {
                strcpy(D_004831F8 + (i << 8), (char *)(ch + 0x214));
            }
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h0 = 0x76;
                    s1->x28->h2 = 8;
                    s1->x28->xC = 0xFF303030;
                }
            }
            if (D_004831F8 != 0) {
                strcpy(D_004831F8 + (i << 8) + 0x80, (char *)(ch + 0x29A));
            }
            o = UiFindWidget_290460(w_w55, idY);
            if (o != 0) {
                if (o->x28 != 0) {
                    o->x28->xC = 0xFF303030;
                    o->x28->bA = 2;
                }
            }
            idD = tbl[7] + id;
            *(Buf16 *)buf = *(Buf16 *)D_0047FAE0;
            v = *(s16 *)(ch + 0x31A);
            q = v / 100;
            r = v % 100;
            buf[10] = q + 0x30;
            UiSetWidgetTexName_290ac0(w_w55, idD, buf);
            o = UiFindWidget_290460(w_w55, idD);
            if (o != 0) {
                cell = (Cell *)o->x20;
                if (cell != 0 && q > 0 && q < 7 && r >= 0 && r < 25) {
                    cell->h8 = (r % 5) * 51;
                    ((Cell *)o->x20)->hA = (r / 5) * 46;
                }
            }
            o = UiFindWidget_290460(w_w55, tbl[1] + id3);
            if (o != 0) {
                q2 = o->x24;
                if (q2 != 0) {
                    SavePlayTimeSplit_3eebf0(ch + 0x50, &a, &b, &c, &d);
                    {
                    u16 t = id + D_00463AF8[sel];
                    if (a > 99) {
                        q2->h10 = 3;
                        UiSetWidgetPos_290f60(w_w55, t, -10, 0);
                    } else {
                        q2->h10 = 2;
                        UiSetWidgetPos_290f60(w_w55, t, 0, 0);
                    }
                    }
                    q2->x8 = a;
                    q2->x28 = b;
                    q2->x48 = c;
                }
            }
            n = *(s16 *)(ch + 0x60);
            for (j_w190 = 0; j_w190 < n; j_w190++) {
                o = UiFindWidget_290460(w_w55, tbl[4] + id);
                if (o != 0) {
                    if (o->x20 != 0) {
                        s16 key;
                        Cell *cl = (Cell *)o->x20;
                        key = *(s16 *)(ch + j_w190 * 40 + 0x76);
                        for (cc = 0; cc < 10; cc++) {
                            if (key == D_00463A40[cc][0]) {
                                cl[j_w190].h0 = j_w190 * 44 + 0x46;
                                cl[j_w190].h2 = 0x3A;
                                cl[j_w190].h8 = D_00463A40[cc][1];
                                cl[j_w190].hA = D_00463A40[cc][2];
                                cl[j_w190].hC = 0x26;
                                cl[j_w190].h4 = 0x26;
                                cl[j_w190].hE = 0x26;
                                cl[j_w190].h6 = 0x26;
                            }
                        }
                        cl[j_w190 + 1].h0 = -1;
                    }
                }
                id5 = tbl[5] + id2;
                UiSetWidgetAlpha_2907a0(w_w55, id5, D_0047D1E8);
                o = UiFindWidget_290460(w_w55, id5);
                v = j_w190 * 44 + 0x46;
                if (o != 0) {
                    if (o->x20 != 0) {
                        ((Cell *)o->x20)[j_w190].h0 = v - 2;
                        ((Cell *)o->x20)[j_w190].h2 = 0x61;
                        ((Cell *)o->x20)[j_w190 + 1].h0 = -1;
                    }
                }
                o = UiFindWidget_290460(w_w55, tbl[6] + id2);
                if (o != 0) {
                    if (o->x20 != 0) {
                        ((Cell *)o->x20)[j_w190].h0 = v;
                        ((Cell *)o->x20)[j_w190].h2 = 0x61;
                        ((Cell *)o->x20)[j_w190 + 1].h0 = -1;
                    }
                    if (o->x24 != 0) {
                        cell = &((Cell *)o->x24)[j_w190];
                        cell->h0 = v + 0x25;
                        cell->h2 = 0x62;
                        *(s64 *)&cell->h8 = *(s16 *)(ch + j_w190 * 40 + 0x78);
                        cell[1].h0 = -1;
                    }
                }
            }
        } else if (SaveSlotEntryIsEmptyAt_3734c0(D_004831D0, no) != 0) {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    ((Sub20 *)s0->x20)->h60 = -1;
                }
            }
            if (sel == 0) {
                UiSetWidgetParent_2911a0(w_w55, idD, idC);
                UiSetWidgetsVisibleById_291110(w_w55, idD, 1, 1);
                UiSetSpritePosSizeUv_28f710(w_w55, idD, 0x9E, 0x3E, 0x68, 0x14, 0, 0x14, 0x68, 0x14, 0);
            }
            if (sel == 1) {
                str = SaveMenuMsgLookup_376b30(0x1A);
                if (D_004831F8 != 0) {
                    if (str != 0) {
                        strcpy(D_004831F8 + (i << 8), str);
                    }
                }
                UiSetTextCenteredX_28f300(w_w55, id5, 0xD8, 0);
                if (s1 != 0) {
                    if (s1->x28 != 0) {
                        s1->x28->h2 = 0x38;
                        s1->x28->xC = 0xFF303030;
                    }
                }
                UiSetWidgetsVisibleById_291110(w_w55, id5, 1, 1);
            }
        } else if (SaveSlotEntryIsNoSpaceAt_373480(D_004831D0, no) != 0) {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    ((Sub20 *)s0->x20)->h60 = -1;
                }
            }
            UiSetWidgetParent_2911a0(w_w55, idD, idC);
            if (sel == 1) {
                str = SaveMenuMsgLookup_376b30(0x1A);
                if (D_004831F8 != 0) {
                    if (str != 0) {
                        strcpy(D_004831F8 + (i << 8), str);
                    }
                }
                UiSetTextCenteredX_28f300(w_w55, id5, 0xD8, 0);
                if (s1 != 0) {
                    if (s1->x28 != 0) {
                        s1->x28->h2 = 0x38;
                        s1->x28->xC = 0xFF303030;
                    }
                }
                UiSetWidgetsVisibleById_291110(w_w55, id5, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(w_w55, idD, 1, 1);
                UiSetSpritePosSizeUv_28f710(w_w55, idD, 0x5E, 0x26, 0xEA, 0x36, 0, 0x4A, 0xEA, 0x36, 0);
            }
        } else {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    ((Sub20 *)s0->x20)->h60 = -1;
                }
            }
            str = SaveMenuMsgLookup_376b30(2);
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i << 8), str);
                }
            }
            UiSetTextCenteredX_28f300(w_w55, id5, 0xD8, 0);
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h2 = 0x38;
                    s1->x28->xC = 0xFF303030;
                }
            }
            UiSetWidgetsVisibleById_291110(w_w55, id5, 1, 1);
        }
    }
}
