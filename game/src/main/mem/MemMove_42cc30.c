/* rgp:protos */
#define RGP_SELF_MemMove_42cc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 MemMove_42cc30(s8 *dst, s8 *src, u32 n)
{
    u32 i;
    s32 k;
    if (dst == 0) goto zero;
    if (src != 0) goto ok;
zero:
    return 0;
ok:
    if (dst == src) return n;
    if (dst < src) {
        i = 0;
        while (i < n) {
            *dst = *src;
            i++;
            src++;
            dst++;
        }
        return n;
    }
    k = n - 1;
    i = 0;
    dst += k;
    src += k;
    while (i < n) {
        *dst = *src;
        i++;
        src--;
        dst--;
    }
    return n;
}
