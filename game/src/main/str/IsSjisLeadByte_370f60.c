/* rgp:protos */
#define RGP_SELF_IsSjisLeadByte_370f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 IsSjisLeadByte_370f60(s32 c)
{
    u8 d = c;
    if ((d >= 0x81 && d <= 0x9F) || (d >= 0xE0 && d <= 0xFF)) {
        return 1;
    }
    return 0;
}
