/* rgp:protos */
#define RGP_SELF_MapIdListGetEntry_1e5a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u8 *MapIdListGetEntry_1e5a50(u8 *base, u32 i)
{
    u8 *r;

    if (i >= 0x14) {
        r = 0;
    } else {
        r = base + i * 8;
    }
    return r;
}
