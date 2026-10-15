#include "types.h"

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

extern s32 GetGameData_1fede0(void);
extern void UiSetWidgetsVisibleById_291110(s32, u16, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, u16, u16);
extern void UiSetWidgetColor_2905b0(s32, u16, f32, f32, f32, f32);
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
extern u16 D_00463B00[];
extern u8 D_0047FAF0[4][2];
extern s32 D_004831D0;
extern s32 D_004831D4;
extern s16 D_004831E8[3];
extern char *D_004831F8;

void SaveSlotListRefresh_377ae0(s32 arg0)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 actor;
    s32 w;
    u16 *tbl;
    s32 i;
    s32 j;
    s16 *p16;
    u16 id;
    u16 idCE;
    u16 idF0;
    u16 idE0;
    u16 idD0;
    u16 idC0;
    u16 idB0;
    u16 id5;
    u16 id1;
    u16 id0;
    s32 no;
    Widget *s1;
    Widget *s0;
    Widget *o;
    u8 *ch;
    s32 x;
    s32 k;
    Sub24 *q;
    s32 base2;
    s32 base2j;
    u8 *e;
    char *str;

    actor = GetGameData_1fede0();
    if (actor == 0) {
        return;
    }
    w = D_004831D4;
    tbl = D_00463B00;
    for (i = 0; i < 3; i++) {
        id = i * 20;
        p16 = &D_004831E8[i];
        j = 0;
        idF0 = id + 0x7FFF + 0x8CF;
        idCE = id + 0x7FFF + 0x8CE;
        idE0 = id + 0x7FFF + 0x8CD;
        *p16 = 0;
        for (; tbl[j] != 0xFFFF; j++) {
            id1 = id + tbl[j]; if (j == 1) id1 = id + tbl[j];
            UiSetWidgetsVisibleById_291110(w, id1, 0, 1);
            UiSetWidgetParent_2911a0(w, id1, idE0);
            UiSetWidgetColor_2905b0(w, idE0, 1.0f, 1.0f, 1.0f, -1.0f);
        }
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1C9B, 0, 1);
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1CA5, 0, 1);
        UiSetWidgetsVisibleById_291110(w, i + 0x7FFF + 0x1CAC, 0, 1);
        id0 = (u16)(s32)id;
        idD0 = id0 + 0x7FFF + 0x8D5;
        UiSetWidgetsVisibleById_291110(w, idD0, 0, 1);
        no = arg0 + i;
        id5 = tbl[2] + id0;
        s1 = UiFindWidget_290460(w, id5);
        idC0 = tbl[3] + id0;
        idB0 = tbl[4] + id0;
        UiSetWidgetSubItemValue_291250(w, idCE, 0, no + 1);
        s0 = UiFindWidget_290460(w, idF0);
        if (D_004831F8 != 0) {
            k = i << 8;
            memset(D_004831F8 + k, 0, 0x100);
            UiSetTextString_28f510(w, id5, D_004831F8 + k, 0);
            UiSetTextString_28f510(w, idC0, D_004831F8 + k + 0x80, 0);
        }
        ch = SlotRecordFindById_3e4e80(actor, no);
        if (SaveSlotEntryIsValidAt_373440(D_004831D0, no) != 0) {
            UiSetWidgetsVisibleById_291110(w, id + 0x7FFF + 0x8D6, 1, 1);
            o = UiFindWidget_290460(w, idF0);
            if (o != 0) {
                if (o->x20 != 0) {
                    o->x20->h60 = 0x6C;
                    o->x20->h80 = 6;
                }
            }
            for (j = 0; tbl[j] != 0xFFFF; j++) {
                id5 = id + tbl[j]; if (j == 1) id5 = id + tbl[j];
                UiSetWidgetParent_2911a0(w, id5, idE0);
                UiSetWidgetsVisibleById_291110(w, id5, 1, 1);
            }
            x = 0;
            UiSetWidgetPos_290f60(w, idB0, 0x53, 6);
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
                UiSetSpriteUv_28f970(w, idB0, D_0047FAF0[k][0], D_0047FAF0[k][1], 0);
            }
            UiSetWidgetsVisibleById_291110(w, idB0, x, 1);
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
                strcpy(D_004831F8 + (i << 8) + 0x80, (char *)(ch + 0x254));
            }
            o = UiFindWidget_290460(w, idC0);
            if (o != 0) {
                if (o->x28 != 0) {
                    o->x28->xC = 0xFF303030;
                    o->x28->bA = 2;
                }
            }
            o = UiFindWidget_290460(w, tbl[1] + id);
            if (o != 0) {
                q = o->x24;
                if (q != 0) {
                    SavePlayTimeSplit_3eebf0(ch + 0x50, &a, &b, &c, &d);
                    {
                    u16 t = id + 0x7FFF + 0x8D0;
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
            base2 = id + 0x7FFF + 0x8D7;
            for (j = 0; j < 3; j++) {
                e = ch + j * 2;
                if (e[0x348] & 1) {
                    base2j = base2 + j;
                    UiSetWidgetsVisibleById_291110(w, base2j, 1, 1);
                    UiSetWidgetSubItemValue_291250(w, base2j, 0, e[0x349]);
                } else {
                    UiSetWidgetsVisibleById_291110(w, base2 + j, 0, 1);
                }
            }
        } else if (SaveSlotEntryIsEmptyAt_3734c0(D_004831D0, no) != 0) {
            UiSetWidgetsVisibleById_291110(w, id + 0x7FFF + 0x8D6, 0, 1);
            base2 = id + 0x7FFF + 0x8D7;
            for (k = 0; k < 3; k++) {
                UiSetWidgetsVisibleById_291110(w, base2 + k, 0, 1);
            }
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            str = SaveMenuMsgLookup_376b30(0x1A);
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i << 8), str);
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
            UiSetWidgetsVisibleById_291110(w, id + 0x7FFF + 0x8D6, 0, 1);
            base2 = id + 0x7FFF + 0x8D7;
            for (k = 0; k < 3; k++) {
                UiSetWidgetsVisibleById_291110(w, base2 + k, 0, 1);
            }
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            UiSetWidgetParent_2911a0(w, idD0, idE0);
            str = SaveMenuMsgLookup_376b30(0x1A);
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i << 8), str);
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
            UiSetWidgetsVisibleById_291110(w, id + 0x7FFF + 0x8D6, 0, 1);
            base2 = id + 0x7FFF + 0x8D7;
            for (k = 0; k < 3; k++) {
                UiSetWidgetsVisibleById_291110(w, base2 + k, 0, 1);
            }
            if (s0 != 0) {
                if (s0->x20 != 0) {
                    s0->x20->h60 = -1;
                    s0->x20->h80 = 6;
                }
            }
            str = SaveMenuMsgLookup_376b30(2);
            if (D_004831F8 != 0) {
                if (str != 0) {
                    strcpy(D_004831F8 + (i << 8), str);
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
