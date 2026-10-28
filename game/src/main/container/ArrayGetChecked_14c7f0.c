/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_14c7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P {
    u8   pad000[0x0C];
    s32  m0C;
    u8   pad010[0x4];
    s32  m14;
    u8  *m18;
} P;

typedef struct O {
    P *m00;
} O;

void *ArrayGetChecked_14c7f0(O *o, s32 i)
{
    P *q; s32 n; u8 *base;
    q = o->m00;
    if (q == 0) return 0;
    if (i < 0) goto fail;
    n = (q != 0) ? q->m0C : 0;
    if (i < n) goto ok;
fail:
    return 0;
ok:
    q = *(P *volatile *)&o->m00;
    base = *(u8 *volatile *)&q->m18;
    return base + q->m14 * i;
}
