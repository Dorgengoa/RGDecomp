/* rgp:protos */
#define RGP_SELF_MapGetAreaSlot_1e5770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void *MapGetAreaSlot_1e5770(u8 *p, u32 i)
{
    void *r;

    if (i >= 4) {
        r = 0;
    } else {
        r = p + i * 0x1CC + 0x1928;
    }
    return r;
}
