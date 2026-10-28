/* rgp:protos */
#define RGP_SELF_Below434db0 1
#define RGP_SELF_Mark434db0 1
#define RGP_SELF_TextEntryBackspace_434db0 1
#include "port/game_protos.h"
#line 1
// build: mwcc b210 + -sdatathreshold 16 (the local s16 tbl[5] initializer object @N must be in .sdata at 0x480350)
#pragma c99 on
#include "types.h"

typedef struct P434db0 {
    u8 pad0[0x14];
    s16 x;
    s16 y;
} P434db0;

typedef struct O434db0 {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x30 - 0x8];
    s8 grid[0xE0 - 0x30];
    s16 sel;
} O434db0;

typedef struct T434db0 {
    s16 v[5];
} T434db0;

/*rgp*/
/*rgp*/
/*rgp*/

static inline s8 Below434db0(O434db0 *o, s16 idx, s16 y)
{
    return (s8)(&((u8 *)o->grid)[idx])[y + 1];
}

static inline void Mark434db0(O434db0 *o, P434db0 *p, T434db0 *tbl, s16 idx, s16 y)
{
    s8 *row = (s8 *)(idx + (s32)o);
    s8 *cell = (s8 *)((u32)row + 0x30) + y;
    s8 c = *cell;

    if (c == '*' || c == ' ') {
        if (tbl->v[o->sel] == idx) {
            *cell = '*';
            TextEntryMarkStarCells_4357b0(o, p->x, p->y);
            TextEntryNameCursorBack_434560(o, p);
        } else {
            s32 b = Below434db0(o, idx, y);

            if (c == '*' || (s8)b == '*') {
                *cell = '*';
                TextEntryMarkStarCells_4357b0(o, p->x, p->y);
                TextEntryNameCursorBack_434560(o, p);
            }
        }
    } else {
        *cell = '*';
        if (o->sel != 0 && tbl->v[o->sel] != idx && row[y + 0x31] != '*') {
            *cell = ' ';
        }
        TextEntryMarkStarCells_4357b0(o, p->x, p->y);
    }
}

void TextEntryBackspace_434db0(O434db0 *o)
{
    P434db0 *p;
    s32 y;
    s32 idx;

    p = ((P434db0 *)UiEntryListFindByTag_28ea40(o->unk4, 0x6D62));
    y = p->y;
    idx = (s16)(p->x + y * 29);
    s16 tbl[5] = {20, 11, 7, 4, 20};
    Mark434db0(o, p, (T434db0 *)tbl, idx, y);
}
