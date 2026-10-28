/* rgp:protos */
#define RGP_SELF_ScreenMarkerGetFlag_31c010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ScreenMarkerGetFlag_31c010(u8 *base, s32 i)
{
    if (i >= 0x20) {
        i = 0x1F;
    }
    return base[i + 0x80] & 0x7F;
}
