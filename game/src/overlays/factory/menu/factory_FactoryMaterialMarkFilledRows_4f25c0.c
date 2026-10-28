/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialMarkFilledRows_4f25c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cell {
    void *f0;
    s16   f4;
    u8    pad06[0x2];
    u8    f8;
    u8    pad09[0x7];
} Cell;

typedef struct Grid {
    u8    pad00[0x8];
    s16   f8;
    u8    pad0A[0x2];
    Cell *f0C;
} Grid;

typedef struct Ctx {
    u8    pad00[0x70];
    Grid *f70;
} Ctx;

typedef struct Slot {
    u8 pad00[0x40];
} Slot;

typedef struct Set {
    u8    pad00[0xC];
    s16   f0C;
    Slot *f10;
} Set;

typedef struct Item {
    u8  pad00[0x4];
    s16 f4;
    s16 f6;
} Item;

typedef struct Owner {
    u8    pad00[0x40];
    void *f40;
} Owner;

typedef struct Pos {
    s16 f0;
} Pos;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMaterialMarkFilledRows_4f25c0(Owner *a)
{
    Grid *g;
    void *h;
    Cell *c;
    Set  *e;
    Item *q;
    void *x;
    void *y;
    s32   i;
    s32   j;
    Slot *p;
    s32   k;

    g = D_00484A48->f70;
    if (g == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        UiSetSpriteSizeUvSize_28f670(a->f40, 0x74, 0, 0, 0, 0, i);
    }
    h = GetFactoryObj_367f30();
    c = g->f0C;
    for (j = 0; j < g->f8; j++, c++) {
        if ((c->f8 & 1) != 0) {
            e = ((Set *)factory_FactoryPartGroupFindById_504080(h, 0xD));
            if (e != 0) {
                p = e->f10;
                for (k = 0; k < e->f0C; k++, p++) {
                    x = factory_FactoryPartObjGetGridX_4fe120(p);
                    y = factory_FactoryPartObjGetGridY_4fe0c0(p);
                    q = ((Item *)factory_FactorySlotFindAt_502ad0(h, x, y));
                    if (q != 0) {
                        if (q->f4 == ((Pos *)c->f0)->f0 && q->f6 == c->f4) {
                            UiSetSpriteSizeUvSize_28f670(a->f40, 0x74, 0x2A, 0x1C, 0x2A, 0x1C, j);
                        }
                    }
                }
            }
        }
    }
}
