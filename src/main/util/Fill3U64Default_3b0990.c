#include "types.h"

/* Known-positive sibling shape of Fill3U64Default_3b0960 (byte-identical, in cunits):
   fill N doublewords from the small-data default and hand the buffer back. */

extern s64 D_00480170;

s64 *Fill3U64Default_3b0990(s64 *dst)
{
    s64 *p;
    s32 n;

    n = 0x3;
    p = dst;
    do {
        *p++ = D_00480170;
        n = n - 1;
    } while (n > 0);
    return dst;
}
