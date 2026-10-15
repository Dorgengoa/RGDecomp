#include "types.h"

struct N2900B0 { u8 pad000[0x88]; struct N2900B0 *f88; struct N2900B0 *f8C; };

s32 UiWidgetAppendSibling_2900b0(void *ctx, struct N2900B0 *a, struct N2900B0 *b)
{
    struct N2900B0 *n;

    if (a == 0) return 0;
    if (b == 0) return 0;
    n = a->f88;
    if (n == 0) {
        b->f8C = a;
        a->f88 = b;
    } else {
        UiWidgetAppendSibling_2900b0(ctx, n, b);
    }
    return 1;
}
