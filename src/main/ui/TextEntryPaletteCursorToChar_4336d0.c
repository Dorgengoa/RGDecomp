#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    u8 padC[8];
    s16 x14;
    s16 x16;
} Cell;

typedef struct {
    void *x0;
    s32 x4;
    u8 pad8[0xD8];
    s16 xE0;
} Ctx;

typedef struct {
    u8 pad0[4];
    s8 *str;
} Ent;

extern void TextEntrySetPageTexts_434160(Ctx *, s32);
extern Ent *UiGetWidgetText_28f620(void *, s32, s32);
extern s32 strlen(const s8 *);
extern Cell *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiGetWidgetPos_2910a0(void *, s32, s32 *, s32 *);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);

void TextEntryPaletteCursorToChar_4336d0(Ctx *arg0, s32 arg1, s8 arg2) {
    Ent *e;
    s8 *str;
    s32 len;
    Cell *c;
    s32 i;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    s32 x3;
    s32 y3;

    switch (arg1) {
    case 0:
        TextEntrySetPageTexts_434160(arg0, 0);
        break;
    case 1:
        TextEntrySetPageTexts_434160(arg0, 1);
        break;
    }
    e = UiGetWidgetText_28f620(arg0->x0, 5, 0);
    if (e == NULL) {
        return;
    }
    str = e->str;
    len = strlen(str);
    if ((u32)(arg1 + 3) < 2) {
        c = UiEntryListFindByTag_28ea40(arg0->x4, 0x6D61);
        if (arg0->xE0 == 0) {
            c->x14 = 0;
            c->x16 = 0;
            UiGetWidgetPos_2910a0(arg0->x0, 4, &x1, &y1);
            UiSetWidgetPos_290f60(arg0->x0, 12, x1 + (c->x4 + c->x14 * c->x8), y1 + (c->x6 + c->x16 * c->xA));
            return;
        }
        for (i = 0; i < len; i++) {
            if (str[i] == '_') {
                c->x14 = i % 18;
                c->x16 = i / 18;
                UiGetWidgetPos_2910a0(arg0->x0, 4, &x2, &y2);
                UiSetWidgetPos_290f60(arg0->x0, 12, x2 + (c->x4 + c->x14 * c->x8), y2 + (c->x6 + c->x16 * c->xA));
                return;
            }
        }
    } else {
        for (i = 0; i < len; i++) {
            if (arg2 == str[i]) {
                c = UiEntryListFindByTag_28ea40(arg0->x4, 0x6D61);
                c->x14 = i % 18;
                c->x16 = i / 18;
                UiGetWidgetPos_2910a0(arg0->x0, 4, &x3, &y3);
                UiSetWidgetPos_290f60(arg0->x0, 12, x3 + (c->x4 + c->x14 * c->x8), y3 + (c->x6 + c->x16 * c->xA));
                return;
            }
        }
    }
}
