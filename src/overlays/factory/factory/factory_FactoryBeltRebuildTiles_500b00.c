#include "types.h"

typedef struct Cell {
    s16 f0;
    s16 f2;
    s16 f4;
} Cell;

typedef struct Pt {
    s16 x;
    s16 y;
    s16 d;
} Pt;

typedef struct Trace {
    Pt *f0;
    u8  pad04[0x2];
    s16 f6;
    u8  pad08[0x4];
} Trace;

typedef struct Map {
    u8     pad000[0x294];
    Cell  *f294;
    s16    f298;
    s16    f29A;
    u8     pad29C[0x10];
    Trace *f2AC;
    s16    f2B0;
} Map;

extern void factory_FactoryBeltTileRemoveAt_500f20(Map *m, s32 x, s32 y);
extern void factory_FactoryBeltTilePlaceAt_501ad0(Map *m, s32 kind, s32 x, s32 y, s32 d);

void factory_FactoryBeltRebuildTiles_500b00(Map *m)
{
    Trace *t;
    Pt    *e;
    Cell  *row;
    s32    i;
    s32    j;
    s32    n;
    s32    k;
    s32    x;
    s32    y;
    s32    d;
    s32    nd;

    if (m->f294 != 0) {
        for (i = 0; i < m->f29A; i++) {
            for (j = 0; j < m->f298; j++) {
                factory_FactoryBeltTileRemoveAt_500f20(m, j, i);
            }
        }
    }
    t = m->f2AC;
    if (t == 0) {
        return;
    }
    for (n = 0; n < m->f2B0; n++, t++) {
        e = t->f0;
        x = e->x;
        y = e->y;
        d = e->d;
        for (k = 1; k < t->f6; k++, e++) {
            nd = e[1].d;
            row = m->f294 + y * m->f298;
            switch (row[x].f0) {
            case -1:
                switch ((nd - d) & 3) {
                case 0:
                    factory_FactoryBeltTilePlaceAt_501ad0(m, 0x13, x, y, d);
                    break;
                case 1:
                    factory_FactoryBeltTilePlaceAt_501ad0(m, 0x14, x, y, (d + 1) & 3);
                    break;
                case 3:
                    factory_FactoryBeltTilePlaceAt_501ad0(m, 0x14, x, y, (d + 2) & 3);
                    break;
                }
                break;
            case 0x13:
            case 0x16:
                factory_FactoryBeltTileRemoveAt_500f20(m, x, y);
                factory_FactoryBeltTilePlaceAt_501ad0(m, 0x15, x, y, d & 3);
                break;
            }
            x = e[1].x;
            y = e[1].y;
            d = nd;
        }
        factory_FactoryBeltTilePlaceAt_501ad0(m, 0x18, x, y, d);
    }
}
