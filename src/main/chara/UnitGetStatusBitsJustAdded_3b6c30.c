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
    volatile M r;
    volatile M b;
    volatile M t;
    M res;
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
