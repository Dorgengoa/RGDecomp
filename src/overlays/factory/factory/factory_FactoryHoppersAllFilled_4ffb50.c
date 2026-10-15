#include "types.h"

typedef struct Slot {
    u8 pad00[0x40];
} Slot;

typedef struct Grid {
    u8    pad00[0xC];
    s16   f0C;
    Slot *f10;
} Grid;

typedef struct Hdr {
    s16 f0;
    s16 f2;
} Hdr;

typedef struct Owner {
    u8   pad00[0x14];
    Hdr *f14;
} Owner;

extern Grid *factory_FactoryPartGroupFindById_504080(void *a, s32 id);
extern void *factory_FactoryPartObjGetGridX_4fe120(Slot *p);
extern void *factory_FactoryPartObjGetGridY_4fe0c0(Slot *p);
extern s32   factory_FactorySlotFindAt_502ad0(void *a, void *x, void *y);

s32 factory_FactoryHoppersAllFilled_4ffb50(Owner *a)
{
    Grid *g;
    Slot *p;
    s32   i;
    void *x;
    void *y;
    s32   n;

    if (a->f14 == 0) {
        return 0;
    }
    g = factory_FactoryPartGroupFindById_504080(a, 0xD);
    if (g == 0) {
        return 0;
    }
    n = 0;
    switch (a->f14->f2) {
    case 0:
        n = 2;
        break;
    case 1:
        n = 3;
        break;
    case 2:
        n = 3;
        break;
    case 3:
        n = 4;
        break;
    case 4:
        n = 4;
        break;
    }
    if (n <= 0) {
        return 0;
    }
    if (g->f0C <= 0) {
        return 0;
    }
    p = g->f10;
    for (i = 0; i < g->f0C; i++, p++) {
        x = factory_FactoryPartObjGetGridX_4fe120(p);
        y = factory_FactoryPartObjGetGridY_4fe0c0(p);
        if (factory_FactorySlotFindAt_502ad0(a, x, y) == 0) {
            return 0;
        }
    }
    return 1;
}
