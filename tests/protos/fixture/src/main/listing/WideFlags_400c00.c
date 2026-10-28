#include "types.h"
/* 64-bit values through 4-byte C (ActCfgTableFindCallNameByFlags_2207b0 shape): the
   caller passes a u64 flag word as `(int)` and mwcc passes the whole `ld`; the callee
   keeps the 8-byte mask of WideGetMask_400c80 in an `s32` local (a `daddu` move) and
   compares `a == (a & mask)` on all 64 bits.  wide-param / wide-arg / wide-local.
   WideNarrow_400cc0 only adds its argument (a 32-bit op): it keeps its s32. */
typedef struct { u32 lo, hi; } Rec;

s64 WideGetMask_400c80(Rec *r)
{
    return ((s64)r->hi << 32) | r->lo;
}

s32 WideFind_400c40(Rec *r, s32 mask)
{
    s32 a;

    a = WideGetMask_400c80(r);
    if (a == (a & mask)) {
        return 1;
    }
    return 0;
}

s32 WideNarrow_400cc0(s32 v)
{
    return v + v;
}

s32 WideCaller_400c00(Rec *r, u64 *flags)
{
    s32 n;

    n = WideFind_400c40(r, (int)*flags);
    return n + WideNarrow_400cc0((int)*flags);
}
