#include "types.h"

/* f18d SESSION 18: the ONLY change from the session-17 park is the
 * DECLARATION ORDER of the two loop counters -- `y` (outer) is declared
 * BEFORE `x` (inner).  That one swap takes the unit from 46 bad words to
 * byte-identical.  Measured by full enumeration of all 720 declaration
 * orders of the six locals in one probe TU: the split is exactly 360/360
 * and `y before x` predicts bad==0 in 720/720 cells.  The other five
 * locals' positions are INERT. */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Rect {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} Rect;

typedef struct Grid {
    u8    pad000[0x234];
    s32   f234;
    u8    pad238[0x68];
    Cell *cells;                                /* 0x2A0 */
    s16   w;                                    /* 0x2A4 */
    s16   h;                                    /* 0x2A6 */
} Grid;

s32 factory_FactoryGridRectIsFree_502d90(Grid *o, Rect *r)
{
    Cell *cells;
    Cell *row;
    Cell *c;
    s32   y;
    s32   x;
    s32   t;

    if (r == 0) {
        return 0;
    }
    if (o->f234 == 0) {
        return 0;
    }
    cells = o->cells;
    if (cells == 0) {
        return 0;
    }
    if (r->x0 > r->x1) {
        return 0;
    }
    if (r->y0 > r->y1) {
        return 0;
    }
    if (r->x1 < 0) {
        return 0;
    }
    if (r->y1 < 0) {
        return 0;
    }
    if (o->w <= r->x0) {
        return 0;
    }
    if (o->h <= r->y0) {
        return 0;
    }
    for (y = r->y0; y <= r->y1; y++) {
        row = &cells[y * o->w];
        for (x = r->x0; x <= r->x1; x++) {
            c = &row[x];
            t = !(c->f04 & 0x8000);
            if (t == 0) {
                return 0;
            }
            if (c->f00 >= 0) {
                return 0;
            }
            if (c->f02 >= 0) {
                return 0;
            }
        }
    }
    return 1;
}
