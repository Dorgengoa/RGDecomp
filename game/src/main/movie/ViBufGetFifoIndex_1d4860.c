/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_ViBufGetFifoIndex_1d4860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ViBufGetFifoIndex_1d4860(u8 *o, s32 arg)
{
    s32 a, b, combined, v0;

    b = *(s32 *)(o + 8);
    a = *(s32 *)(o + 4);
    b = b + 1;
    combined = a + (b << 4);
    combined = (combined);
    if (arg == combined) {
        return 0;
    }
    v0 = *(s32 *)(o + 0);
    return (u32)(arg - v0) >> 11;
}
