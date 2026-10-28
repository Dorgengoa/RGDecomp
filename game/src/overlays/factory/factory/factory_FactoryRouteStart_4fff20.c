/* rgp:protos */
#define RGP_SELF_factory_FactoryRouteStart_4fff20 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryRouteStart_4fff20(void *w, Out *out, s32 a, s32 b)
{
    Rec  *r;
    void *h;
    s16   kind;

    if (out == 0) {
        return 0;
    }
    r = ((Rec *)factory_FactoryGridCellAt_5037f0(w, a, b));
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
    if (((s32)factory_FactoryPartGroupGetObj_4fea80(h, r->f02)) == 0) {
        return 0;
    }
    out->f00 = r->f00;
    out->f02 = r->f02;
    out->f04 = 0;
    return 1;
}
