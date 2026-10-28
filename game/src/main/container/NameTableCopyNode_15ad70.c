/* rgp:protos */
#define RGP_SELF_NameTableCopyNode_15ad70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u8 *NameTableCopyNode_15ad70(u8 *dst, u8 *src)
{
    u64 *d;
    u64 *s;
    s32 i;

    d = (u64 *)dst;
    s = (u64 *)src;
    i = 13;
    do {
        *d = *s;
        i--;
        s++;
        d++;
    } while (i > 0);
    return dst;
}
