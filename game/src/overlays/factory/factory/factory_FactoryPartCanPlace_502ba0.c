/* rgp:protos */
#define RGP_SELF_factory_FactoryPartCanPlace_502ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rect {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} Rect;

typedef struct Span {
    s32 f0;
    s32 f4;
} Span;

typedef struct Map {
    u8  pad000[0x2A4];
    s16 f2A4;
    s16 f2A6;
    u8  pad2A8[0xC];
    s32 f2B4;
} Map;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryPartCanPlace_502ba0(Map *m, void *b, void *c, float rgp_f0, float rgp_f1)
{
    Rect r __attribute__((aligned(16)));
    Span p __attribute__((aligned(16)));
    Span q __attribute__((aligned(16)));
    s32  i;
    s32  k;

    if (b == 0) {
        return 0;
    }
    factory_FactoryPartFootprintRect_502760(m, &r, b, c, (float)rgp_f0, (float)rgp_f1);
    if (r.f0 < 0) {
        return 0;
    }
    if (r.f2 < 0) {
        return 0;
    }
    if (m->f2A4 <= r.f4) {
        return 0;
    }
    if (m->f2A6 <= r.f6) {
        return 0;
    }
    i = 0;
    while (factory_FactoryPartDefGetGridRect_4fe480(b, &p, &r, c, i) != 0) {
        i++;
        if (factory_FactoryGridRectIsFree_502d90(m, &p) == 0) {
            return 0;
        }
    }
    r.f0 = r.f0 * m->f2B4;
    r.f2 = r.f2 * m->f2B4;
    r.f4 = (r.f4 + 1) * m->f2B4 - 1;
    r.f6 = (r.f6 + 1) * m->f2B4 - 1;
    k = 0;
    while (factory_FactoryPartDefGetFineGridRect_4fe4a0(b, &q, &r, c, k) != 0) {
        k++;
        if (factory_FactoryFineGridRectIsFree_502ef0(m, &q) == 0) {
            return 0;
        }
    }
    return 1;
}
