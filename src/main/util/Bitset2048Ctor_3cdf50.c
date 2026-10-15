#include "types.h"

/* Known-positive sibling shape of Fill3U64Default_3b0960 (byte-identical, in cunits):
   fill N doublewords from the small-data default and hand the buffer back. */

extern s64 D_004801D0;

s64 *Bitset2048Ctor_3cdf50(s64 *dst)
{
    s64 *p;
    s32 n;

    n = 0x20;
    p = dst;
    do {
        *p++ = D_004801D0;
        n = n - 1;
    } while (n > 0);
    return dst;
}
