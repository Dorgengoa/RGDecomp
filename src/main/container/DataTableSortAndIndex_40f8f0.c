#include "types.h"

typedef struct Cell {
    s16 a;
    s16 b;
} Cell;

typedef struct Ent {
    u8 pad0[2];
    s16 x2;
    u8 pad4[6];
    s16 xA;
    u8 padC[0x14];
    u8 *x20;
    u8 pad24[0x18];
} Ent;

typedef struct Obj {
    u8 pad0[0x7A];
    u8 f0 : 1;
    u8 fr : 7;
    u8 pad7B;
    s16 x7C;
    u8 pad7E[0xE];
    Ent *x8C;
    u8 pad90[8];
    Cell grid[10][21];
} Obj;

extern u8 DataTableBubbleSort_368220(void);
extern s32 MainCharaIdToNumber_4016b0(s32);

s32 DataTableSortAndIndex_40f8f0(Obj *arg0)
{
    u8 v;
    s32 i;
    s32 j;
    Ent *p;
    s32 k;
    s32 r;
    s32 c;
    Cell *e;

    v = DataTableBubbleSort_368220();
    arg0->f0 = 0;
    if (v == 0) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 21; j++) {
            arg0->grid[i][j].a = -1;
            arg0->grid[i][j].b = -1;
        }
    }
    p = arg0->x8C;
    for (k = 0; k < arg0->x7C; k++, p++) {
        r = MainCharaIdToNumber_4016b0(p->x2) - 1;
        if (r < 0 || r >= 9) {
            r = 9;
        }
        c = 20;
        if (p->xA > 0 && p->x20 != 0) {
            c = *p->x20;
            if (c >= 20) {
                c = 20;
            }
        }
        if (arg0->grid[r][c].a < 0) {
            arg0->grid[r][c].a = k;
        }
        arg0->grid[r][c].b = k;
    }
    return 1;
}
