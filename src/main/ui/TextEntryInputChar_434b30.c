#include "types.h"
#pragma opt_propagation off

typedef struct {
    s32 x0;
    s32 x4;
} Obj;

typedef struct {
    u8 pad0[4];
    s32 x4;
} V1;

typedef struct {
    u8 pad0[0x14];
    s16 x14;
    s16 x16;
} V2;

extern V1 *UiGetWidgetText_28f620(s32, s32, s32);
extern V2 *UiEntryListFindByTag_28ea40(s32, s32);
extern void TextEntryTogglePage_434230(Obj *);
extern void TextEntryCommit_4348b0(Obj *);
extern void TextEntryBackspace_434db0(Obj *);
extern void TextEntryFillGapSpaces_435530(Obj *, s8 *, s16);
extern void TextEntryMarkStarCells_4357b0(Obj *, s32, s32);
extern s32 TextEntryNameCursorAdvance_434690(Obj *, V2 *);
extern void TextEntryCursorToCommitKey_434d30(Obj *);

void TextEntryInputChar_434b30(Obj *self)
{
    s16 off17;
    s16 off29;
    s32 flag;
    s8 type;
    s16 h14;
    s32 base;
    s8 c;
    s8 *row;
    V1 *v;
    s16 co;
    V2 *a;
    V2 *b;
    s32 h16;

    v = UiGetWidgetText_28f620(self->x0, 5, 0);
    if (v == NULL) {
        return;
    }
    base = v->x4;
    a = UiEntryListFindByTag_28ea40(self->x4, 0x6D61);
    h16 = a->x16;
    h14 = a->x14;
    off17 = h14 + h16 * 17;
    off29 = h14 + h16 * 29;
    b = UiEntryListFindByTag_28ea40(self->x4, 0x6D62);
    co = b->x14 + b->x16 * 29;
    flag = 0;
    type = *(s8 *)(off29 + (s32)self + 0xE8);
    switch (type) {
    case 0x41:
        TextEntryTogglePage_434230(self);
        break;
    case 0x42:
        TextEntryBackspace_434db0(self);
        break;
    case 0x43:
        TextEntryCommit_4348b0(self);
        break;
    case 0x44:
        *(u8 *)(b->x16 + (co + (s32)self) + 0x30) = 0x20;
        TextEntryFillGapSpaces_435530(self, (s8 *)0x20, co);
        TextEntryMarkStarCells_4357b0(self, b->x14, b->x16);
        flag = TextEntryNameCursorAdvance_434690(self, b) & 0xFF;
        break;
    default:
        row = (s8 *)(base + off17);
        c = row[(s16)h16];
        *(u8 *)(b->x16 + (co + (s32)self) + 0x30) = c;
        TextEntryFillGapSpaces_435530(self, row, co);
        TextEntryMarkStarCells_4357b0(self, b->x14, b->x16);
        flag = TextEntryNameCursorAdvance_434690(self, b) & 0xFF;
        break;
    }
    if (flag != 0) {
        TextEntryCursorToCommitKey_434d30(self);
    }
}
