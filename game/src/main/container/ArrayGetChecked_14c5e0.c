/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_14c5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P {
    u8   pad000[0x2C];
    s32  m2C;
    s32  m30;
    u8  *m34;
} P;

typedef struct O {
    P *m00;
} O;

void *ArrayGetChecked_14c5e0(O *o, s32 i)
{
    P *q; s32 n; u8 *base;
    q = o->m00;
    if (q == 0) return 0;
    if (i < 0) goto fail;
    n = (q != 0) ? q->m2C : 0;
    if (i < n) goto ok;
fail:
    return 0;
ok:
    q = *(P *volatile *)&o->m00;
    base = *(u8 *volatile *)&q->m34;
    return base + q->m30 * i;
}
