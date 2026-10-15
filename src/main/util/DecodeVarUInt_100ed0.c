#include "types.h"
u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval)
{
    u32 val = p[0];
    u32 b1, b2;
    if (!(val & 1)) {
        *pval = val >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(val & 2)) {
        *pval = ((val >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(val & 4)) {
        *pval = ((val >> 3) << 16) | (b1 << 8) | b2;
        return p + 3;
    }
    *pval = ((val >> 3) << 24) | (b1 << 16) | (b2 << 8) | p[3];
    return p + 4;
}
