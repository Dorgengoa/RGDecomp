#include "types.h"

/* Known-positive sibling shape of Fill3U64Default_3b0960 (byte-identical, in cunits):
   fill N doublewords from the small-data default and hand the buffer back. */

extern s64 D_004801C0;

s64 *Bitset1280Ctor_3cdfb0(s64 *dst)
{
    s64 *p;
    s32 n;

    n = 0x14;
    p = dst;
    do {
        *p++ = D_004801C0;
        n = n - 1;
    } while (n > 0);
    return dst;
}
