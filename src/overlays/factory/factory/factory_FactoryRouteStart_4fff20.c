#include "types.h"

typedef struct Rec {
    s16 f00;
    s16 f02;
} Rec;

typedef struct Out {
    s16 f00;
    s16 f02;
    s16 f04;
} Out;

extern Rec  *factory_FactoryGridCellAt_5037f0(void *w, s32 a, s32 b);
extern void *factory_FactoryPartGroupFindById_504080(void *w, s16 kind);
extern s32   factory_FactoryPartGroupGetObj_4fea80(void *h, s16 id);

s32 factory_FactoryRouteStart_4fff20(void *w, Out *out, s32 a, s32 b)
{
    Rec  *r;
    void *h;
    s16   kind;

    if (out == 0) {
        return 0;
    }
    r = factory_FactoryGridCellAt_5037f0(w, a, b);
    if (r == 0) {
        return 0;
    }
    kind = r->f00;
    if (kind != 0xD) {
        return 0;
    }
    h = factory_FactoryPartGroupFindById_504080(w, kind);
    if (h == 0) {
        return 0;
    }
    if (factory_FactoryPartGroupGetObj_4fea80(h, r->f02) == 0) {
        return 0;
    }
    out->f00 = r->f00;
    out->f02 = r->f02;
    out->f04 = 0;
    return 1;
}
