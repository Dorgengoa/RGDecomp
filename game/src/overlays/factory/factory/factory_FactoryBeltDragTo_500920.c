/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltDragTo_500920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Part {
    Cell *f00;
    s16   f04;
    s16   f06;
    s16   f08;
    u8    pad0A[0x2];
} Part;                                         /* 0xC */

typedef struct Node {
    u8  pad00[0xC];
    s16 f0C;
    s16 f0E;
    u8  pad10[0x4];
} Node;                                         /* 0x14 */

typedef struct Grid {
    u8    pad000[0xCC];
    Node *f0CC;
    s32   f0D0;
    u8    pad0D4[0x1D8];
    Part *f2AC;
    s16   f2B0;
} Grid;

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryBeltDragTo_500920(Grid *o, s32 a, s32 b, s32 c)
{
    Part *part;
    Cell *cur;
    Cell *prev;
    Cell *cc;
    Node *q;
    s32   i;
    s32   j;
    s32   x;
    s32   y;
    s32   t;
    s32   v;
    u8    flag;

    part = ((Part *)factory_FactoryBeltGet_503e50(o, a));
    if (part == 0) {
        return 0;
    }
    for (i = 0; i < o->f2B0; i++) {
        Part *pp = (Part *)(i * 12 + (s32)o->f2AC);
        pp->f08 = pp->f06;
    }
    cur = &part->f00[part->f08];
    prev = cur - 1;
    if (prev->f00 == b && prev->f02 == c) {
        return 1;
    }
    cc = ((Cell *)factory_FactoryFineGridCellAt_503880(o, prev->f00, prev->f02));
    if (cc == 0) {
        return 0;
    }
    t = !(cc->f04 & 0x8000);
    if (t == 0) {
        return 0;
    }
    q = o->f0CC;
    if (q != 0) {
        for (j = 0; j < o->f0D0; j++, q++) {
            q->f0E = q->f0C;
        }
    }
    factory_FactoryBeltExtendToward_500630(o, a, b, c);
    while (part->f08 > part->f06) {
        flag = 0;
        cur = &part->f00[part->f08];
        x = cur[-1].f00;
        y = cur[-1].f02;
        cc = ((Cell *)factory_FactoryFineGridCellAt_503880(o, x, y));
        if (cc != 0) {
            t = !(cc->f04 & 0x8000);
            if (t != 0) {
                v = cc->f00;
                flag = 1;
                switch (v) {
                case 0x13:
                case 0x16:
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) {
            break;
        }
        part->f08 = part->f08 - 1;
    }
    return 1;
}
