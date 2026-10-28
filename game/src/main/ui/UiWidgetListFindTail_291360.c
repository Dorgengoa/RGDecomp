/* rgp:protos */
#define RGP_SELF_UiWidgetListFindTail_291360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N {
    struct N *f0;
    u8 pad4[4];
    struct N *f8;
} N;

typedef struct S {
    N *f0;
} S;

N *UiWidgetListFindTail_291360(S *self, N *p)
{
    N *r;
    if (p != 0) goto ok;
    p = self->f0;
ok:
    r = 0;
    while (p != 0) {
        if (p->f0 == 0) goto out;
        r = p;
        p = p->f8;
    }
out:
    return r;
}
