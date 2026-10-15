#include "types.h"
typedef unsigned long long U64;
struct B48 { U64 v; };
struct TFUN_003b6be0 { u8 pad000[0xC8]; struct B48 fC8; u8 pad0D0[0xD8]; struct B48 f1A8; u8 pad1B0[0x8]; struct B48 f1B8; };
struct B48 UnitGetStatusBitsJustCleared_3b6be0(struct TFUN_003b6be0 *t)
{
    volatile U64 r;
    volatile U64 a;
    volatile U64 m;
    struct B48 out;
    U64 av, bv, mv, rv;

    av = t->fC8.v;
    bv = t->f1A8.v;
    a = av;
    mv = ~av & 0x0000FFFFFFFFFFFFULL;
    rv = bv & mv;
    m = mv;
    r = rv;
    out.v = rv;
    return out;
}
