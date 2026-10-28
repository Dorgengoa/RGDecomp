/* rgp:protos */
#define RGP_SELF_TextEntryInputChar_434b30 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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

    v = ((V1 *)UiGetWidgetText_28f620(self->x0, 5, 0));
    if (v == NULL) {
        return;
    }
    base = v->x4;
    a = ((V2 *)UiEntryListFindByTag_28ea40(self->x4, 0x6D61));
    h16 = a->x16;
    h14 = a->x14;
    off17 = h14 + h16 * 17;
    off29 = h14 + h16 * 29;
    b = ((V2 *)UiEntryListFindByTag_28ea40(self->x4, 0x6D62));
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
        TextEntryFillGapSpaces_435530(self);
        TextEntryMarkStarCells_4357b0(self, b->x14, b->x16);
        flag = ((unsigned char)TextEntryNameCursorAdvance_434690(self, b)) & 0xFF;
        break;
    default:
        row = (s8 *)(base + off17);
        c = row[(s16)h16];
        *(u8 *)(b->x16 + (co + (s32)self) + 0x30) = c;
        TextEntryFillGapSpaces_435530(self);
        TextEntryMarkStarCells_4357b0(self, b->x14, b->x16);
        flag = ((unsigned char)TextEntryNameCursorAdvance_434690(self, b)) & 0xFF;
        break;
    }
    if (flag != 0) {
        TextEntryCursorToCommitKey_434d30(self);
    }
}
