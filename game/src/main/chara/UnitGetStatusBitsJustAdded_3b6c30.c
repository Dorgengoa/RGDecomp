/* rgp:protos */
#define RGP_SELF_UnitGetStatusBitsJustAdded_3b6c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct M {
    u64 v;
} M;

typedef struct O {
    u8 pad000[0xC8];
    M mA;
    u8 padA[0x1A8 - 0xC8 - 8];
    M mB;
} O;

M UnitGetStatusBitsJustAdded_3b6c30(O *o)
{
    volatile M r __attribute__((aligned(16)));
    volatile M b __attribute__((aligned(16)));
    volatile M t __attribute__((aligned(16)));
    M res __attribute__((aligned(16)));
    u64 bv;
    u64 tv;

    bv = o->mB.v;
    b.v = bv;
    tv = ~bv & 0xFFFFFFFFFFFFULL;
    t.v = tv;
    res.v = tv & o->mA.v;
    r.v = res.v;
    return res;
}
