/* rgp:protos */
#define RGP_SELF_Bitset131072Ctor_3eeee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of Fill3U64Default_3b0960 (byte-identical, in cunits):
   fill N doublewords from the small-data default and hand the buffer back. */

extern s64 D_00480210;

s64 *Bitset131072Ctor_3eeee0(s64 *dst)
{
    s64 *p;
    s32 n;

    n = 0x800;
    p = dst;
    do {
        *p++ = D_00480210;
        n = n - 1;
    } while (n > 0);
    return dst;
}
