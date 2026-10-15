#include "types.h"

typedef struct S { u8 b[1]; } S;

extern double UIntToDouble_100320(u8 v);
extern double dpmul(double a, double b);

f32 MapDataGetColorG_1e7590(S *o)
{
    return dpmul(0.00390625, UIntToDouble_100320(o->b[0x51]));
}
