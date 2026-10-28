/* rgp:protos */
#define RGP_SELF_ListAppendTail_1ef9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1EF9E0 { struct T1EF9E0 *f0; struct T1EF9E0 *f4; };

void ListAppendTail_1ef9e0(struct T1EF9E0 *p, struct T1EF9E0 *q)
{
    struct T1EF9E0 *n;

    n = p->f4;
    if (n != 0) {
        ListAppendTail_1ef9e0(n, q);
    } else {
        q->f0 = p;
        p->f4 = q;
    }
}
