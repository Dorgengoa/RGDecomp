/* rgp:protos */
#define RGP_SELF_InsectVsSaveSlotListRefreshMaybe_37ab70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

typedef struct Sub20 {
    u8 pad0[0x60];
    s16 h60;            /* +0x60 */
    u8 pad62[0x1E];
    s16 h80;            /* +0x80 */
} Sub20;

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
    Sub20 *x20;         /* +0x20 */
    Sub24 *x24;         /* +0x24 */
    Sub28 *x28;         /* +0x28 */
} Widget;

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

/*rgp*/
extern s32 func_4F3320(void);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u16 D_00463A68[];
extern u16 D_00463A78[];
extern u16 D_00463A7C[];
extern Pair D_0047FAB0;
extern u8 D_0047FAB8[4][2];
extern s32 D_004831D0;
extern s32 D_004831D4;
extern s16 D_004831E8[3];
extern char *D_004831F8;

void InsectVsSaveSlotListRefreshMaybe_37ab70(s32 arg0)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 actor;
    s32 msg;
    s32 w;
    u16 *tbl;
    s32 i;
    s32 j;
    s32 i2;
    s16 *p16;
    u16 m1;
    u32 m2;
    u16 id;
    u16 id2;
    u16 idCE;
    u16 idF0;
    u16 idE0;
    u16 idC0;
    u16 id5;
    u16 id1;
    u16 id0;
    s32 base;
    u16 t1C;
    s32 no;
    Widget *s1;
    Widget *s0;
    Widget *o;
    u8 *ch;
    s32 x;
    s32 k;
    Sub24 *q;
    s32 pr[2];
    char *str;

    actor = ((s32)GetGameData_1fede0());
    if (actor == 0) {
        return;
    }
    tbl = D_00463A68;
    w = D_004831D4;
    m1 = D_00463A78[0];
    m2 = D_00463A7C[0];
    for (i = 0; i < 3; i++) {
        id = m1 * i;
        base = id + 0x7FFF + 0x8D7;
        for (j = 0; j < 3; j++) {
            UiSetWidgetsVisibleById_291110(w, base + j, 0, 1);
        }
        id0 = (u16)(s32)id;
        UiSetWidgetsVisibleById_291110(w, id0 + 0x7FFF + 0x8D6, 0, 1);
        UiSetWidgetsVisibleById_291110(w, id0 + 0x7FFF + 0x8D3, 0, 1);
    }
    msg = func_4F3320();
    m2 = (u16)m2;
    for (i2 = 0; i2 < 3; i2++) {
        id = m1 * i2;
        id2 = m2 * i2;
        p16 = &D_004831E8[i2];
        j = 0;
        idCE = id + 0x7FFF + 0x8CE;
        *p16 = 0;
        idF0 = id + 0x7FFF + 0x8CF;
        idE0 = id + 0x7FFF + 0x8CD;
        for (; tbl[j] != 0xFFFF; j++) {
            id1 = id + tbl[j]; if (j == 1) id1 = id2 + tbl[j];
            UiSetWidgetsVisibleById_291110(w, id1, 0, 1);
            UiSetWidgetParent_2911a0(w, id1, idE0);
            UiSetWidgetColor_2905b0(w, idE0, 1.0f, 1.0f, 1.0f, -1.0f);
        }
        *(Pair *)pr = D_0047FAB0;
        k = 0;
        do {
            UiSetWidgetsVisibleById_291110(w, pr[0], 0, 1);
            UiSetWidgetsVisibleById_291110(w, pr[1], 0, 1);
            k++;
            pr[0]++;
            pr[1]++;
        } while (k < 3);
        UiSetWidgetsVisibleById_291110(w, i2 + 0x7FFF + 0x1CAC, 0, 1);
        id0 = (u16)(s32)id;
        no = arg0 + i2;
        id5 = tbl[2] + id0;
        s1 = ((Widget *)UiFindWidget_290460(w, id5));
        idC0 = tbl[3] + id0;
        UiSetWidgetSubItemValue_291250(w, idCE, 0, no + 1);
        UiSetSpriteX_28fcd0(w, idCE, 9, 0);
        UiSetSubItemX_28f1c0(w, idCE, 0x4E, 0);
        s0 = ((Widget *)UiFindWidget_290460(w, idF0));
        if (D_004831F8 != 0) {
            k = i2 << 8;
            memset(D_004831F8 + k, 0, 0x100);
            UiSetTextString_28f510(w, id5, D_004831F8 + k, 0);
        }
        ch = ((u8 *)SlotRecordFindById_3e4e80(actor, no));
        if (SaveSlotEntryIsValidAt_373440(D_004831D0, no) != 0) {
            o = ((Widget *)UiFindWidget_290460(w, idF0));
            if (o != 0) {
                if (o->x20 != 0) {
                    o->x20->h60 = 0x6C;
                    o->x20->h80 = -1;
                }
            }
            for (j = 0; tbl[j] != 0xFFFF; j++) {
                id5 = id + tbl[j]; if (j == 1) id5 = id2 + tbl[j];
                UiSetWidgetParent_2911a0(w, id5, idE0);
                UiSetWidgetsVisibleById_291110(w, id5, 1, 1);
            }
            x = 0;
            UiSetWidgetPos_290f60(w, idC0, 0x53, 6);
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
                UiSetSpriteUv_28f970(w, idC0, D_0047FAB8[k][0], D_0047FAB8[k][1], 0);
            }
            UiSetWidgetsVisibleById_291110(w, idC0, x, 1);
            *p16 = *(u16 *)(ch + 0x338);
            if (D_004831F8 != 0) {
                strcpy(D_004831F8 + (i2 << 8), (char *)(ch + 0x214));
            }
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h0 = 0x76;
                    s1->x28->h2 = 8;
                    s1->x28->xC = 0xFF303030;
                }
            }
            o = ((Widget *)UiFindWidget_290460(w, tbl[1] + id2));
            if (o != 0) {
                q = o->x24;
                if (q != 0) {
                    SavePlayTimeSplit_3eebf0(ch + 0x50, &a, &b, &c, &d);
                    {
                    u16 t = id + 0x7565;
                    if (a > 99) {
                        q->h10 = 3;
                        UiSetWidgetPos_290f60(w, t, -10, 0);
                    } else {
                        q->h10 = 2;
                        UiSetWidgetPos_290f60(w, t, 0, 0);
                    }
                    }
                    q->x8 = a;
                    q->x28 = b;
                    q->x48 = c;
                }
            }
            t1C = i2 + 0x7FFF + 0x1CAC;
            UiSetWidgetsVisibleById_291110(w, t1C, 1, 1);
            UiSetTextString_28f510(w, t1C, ((char *)MsgTableLookup_28aa30(msg, 0x640)), 0);
            UiSetWidgetSubItemValue_291250(w, t1C, 0, ch[0x34E]);
        } else if (SaveSlotEntryIsEmptyAt_3734c0(D_004831D0, no) != 0) {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            str = ((char *)SaveMenuMsgLookup_376b30(0x1A));
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i2 << 8), str);
                }
            }
            UiSetTextCenteredX_28f300(w, id5, 0xD8, 0);
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h2 = 0x38;
                    s1->x28->xC = 0xFF303030;
                }
            }
            UiSetWidgetsVisibleById_291110(w, id5, 1, 1);
        } else if (SaveSlotEntryIsNoSpaceAt_373480(D_004831D0, no) != 0) {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            str = ((char *)SaveMenuMsgLookup_376b30(0x1A));
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i2 << 8), str);
                }
            }
            UiSetTextCenteredX_28f300(w, id5, 0xD8, 0);
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h2 = 0x38;
                    s1->x28->xC = 0xFF303030;
                }
            }
            UiSetWidgetsVisibleById_291110(w, id5, 1, 1);
        } else {
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            str = ((char *)SaveMenuMsgLookup_376b30(2));
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i2 << 8), str);
                }
            }
            UiSetTextCenteredX_28f300(w, id5, 0xD8, 0);
            if (s1 != 0) {
                if (s1->x28 != 0) {
                    s1->x28->h2 = 0x38;
                    s1->x28->xC = 0xFF303030;
                }
            }
            UiSetWidgetsVisibleById_291110(w, id5, 1, 1);
        }
    }
}
