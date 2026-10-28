#include "types.h"
/* soft-double callers that typed the 64-bit GPR as s64 / s32 */
extern s64 dpmul(s64, s64);
extern s64 fptodp(f32);
extern f32 dptofp(s64);

f32 SoftMul_100000(f32 a, f32 b)
{
    return dptofp(dpmul(fptodp(a), fptodp(b)));
}

s64 SoftMulBits_100010(f32 a, f32 b)
{
    s64 x;
    s64 y;

    x = fptodp(a);
    y = fptodp(b);
    return dpmul(x, y);
}

f32 SoftMulInt_100020(f32 a, f32 b)
{
    s32 x;
    s32 y;

    x = fptodp(a);
    y = fptodp(b);
    return dptofp(dpmul(x, y));
}
