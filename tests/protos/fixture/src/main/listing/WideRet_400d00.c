#include "types.h"
/* 64-bit values returned through 4-byte C (ActDataCnctGetCmndMask_2274c0 shape): the
   wrapper is declared s32 but leaves the 8-byte getter's $v0 untouched (wide-ret, and
   its `s32 m` local: wide-local); the accumulator `s32 r; r |= ..` returns all 64 bits
   (wide-ret + wide-local `|=`); the static inline helper takes the caller's u64 mask
   as `u32` (wide-inline-param): mwcc inlined it and compares all 64 bits. */
typedef struct { u32 lo, hi; } Rec2;

s64 WideRetGet_400da0(Rec2 *r)
{
    return ((s64)r->hi << 32) | r->lo;
}

s32 WideRetWrap_400d60(Rec2 *r)
{
    s32 m;

    if (r == 0) {
        return 0;
    }
    m = WideRetGet_400da0(r);
    return m;
}

s32 WideRetOr_400dc0(Rec2 *r, s32 n)
{
    s32 acc;
    s32 i;

    acc = 0;
    for (i = 0; i < n; i++) {
        acc |= WideRetWrap_400d60(r + i);
    }
    return acc;
}

static inline s32 WideMatch(Rec2 *r, u32 mask)
{
    return (mask & WideRetWrap_400d60(r)) == WideRetWrap_400d60(r);
}

s32 WideRetFind_400d00(Rec2 *r, u64 mask, u64 *out)
{
    *out = WideRetOr_400dc0(r, 2);
    return WideMatch(r, mask);
}
