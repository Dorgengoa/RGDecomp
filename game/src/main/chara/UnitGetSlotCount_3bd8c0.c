/* rgp:protos */
#define RGP_SELF_UnitGetSlotCount_3bd8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct A3BD8C0 { u8 pad000[0x78]; s16 m78; } A3BD8C0;
typedef struct P3BD8C0 { u8 pad000[0x234]; A3BD8C0 *m234; } P3BD8C0;
s32 UnitGetSlotCount_3bd8c0(P3BD8C0 *p)
{
    A3BD8C0 *q;
    s32      v;

    q = p->m234;
    if (q == 0) return 0;
    v = q->m78;
    /* `slti $1` is the $at compare class: `v > 8`, not `v >= 9`. */
    if (v > 8) v = 8;
    return v;
}
