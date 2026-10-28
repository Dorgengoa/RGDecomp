/* rgp:protos */
#define RGP_SELF_UiWidgetAppendChild_290100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct N290100 { u8 pad000[0x90]; struct N290100 *f90; };

/*rgp*/

s32 UiWidgetAppendChild_290100(void *ctx, struct N290100 *a, struct N290100 *b)
{
    struct N290100 *n;

    if (a == 0) return 0;
    if (b == 0) return 0;
    n = a->f90;
    if (n == 0) goto store;
    UiWidgetAppendSibling_2900b0(ctx, n, b);
    return 1;
store:
    a->f90 = b;
    return 1;
}
