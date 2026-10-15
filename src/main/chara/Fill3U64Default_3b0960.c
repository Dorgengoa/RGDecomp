#include "types.h"

/* Fill three doublewords from the small-data default, and hand the buffer
   back.  Bottom-tested do/while; the two unfilled slots around the bgtz are
   what the reference shows. */

extern s64 D_00480178;

s64 *Fill3U64Default_3b0960(s64 *dst)
{
    s64 *p;
    s32 n;

    n = 3;
    p = dst;
    do {
        *p++ = D_00480178;
        n = n - 1;
    } while (n > 0);
    return dst;
}
