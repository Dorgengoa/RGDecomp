#include "types.h"
/* ret-zext (ParseFlagNames_1ca700 shape): the parser returns s32, the attr-flag
   builder's own view said u32 and retail zero-extends each result (dsll32/dsrl32)
   before OR-ing it into the u64.  Staged against the s32 definition, `hi | F()`
   sign-extended bit 31 into the high word.  ZextNeg_400f00 uses the s32 value as
   s64 with retail's sign extension: no cast. */
s32 ZextParse_400e40(const char *s)
{
    s32 r;

    r = 0;
    while (*s) {
        r = (r << 1) | (*s++ & 1);
    }
    return r;
}

u64 ZextCombine_400e80(const char *a, const char *b)
{
    u64 hi;

    hi = (u64)ZextParse_400e40(a) << 32;
    return hi | ZextParse_400e40(b);
}

s64 ZextNeg_400f00(const char *a)
{
    return ZextParse_400e40(a);
}
