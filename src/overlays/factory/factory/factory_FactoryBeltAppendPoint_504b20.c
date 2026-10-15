#include "types.h"

typedef struct Pt {
    s16 x;
    s16 y;
    s16 d;
} Pt;

typedef struct Path {
    Pt *pts;
    s16 cap;
    s16 n;
} Path;

s32 factory_FactoryBeltAppendPoint_504b20(Path *p, s32 x, s32 y)
{
    Pt *e;
    Pt *q;
    s32 d;

    if (p->pts == 0 || p->n <= 0 || p->cap <= p->n) {
        return 0;
    }
    e = &p->pts[p->n];
    q = e - 1;
    e->x = x;
    p->pts[p->n].y = y;
    if (q->x == x) {
        if (q->y == y) {
            return 0;
        }
        d = y - q->y;
        switch (d) {
        case 1:
            p->pts[p->n].d = 0;
            p->n = p->n + 1;
            return 1;
        case -1:
            p->pts[p->n].d = 2;
            p->n = p->n + 1;
            return 1;
        }
        return 0;
    }
    if (q->y == y) {
        if (q->x == x) {
            return 0;
        }
        d = x - q->x;
        switch (d) {
        case 1:
            p->pts[p->n].d = 1;
            p->n = p->n + 1;
            return 1;
        case -1:
            p->pts[p->n].d = 3;
            p->n = p->n + 1;
            return 1;
        }
        return 0;
    }
    return 0;
}
