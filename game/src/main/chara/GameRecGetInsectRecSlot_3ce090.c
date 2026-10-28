/* rgp:protos */
#define RGP_SELF_GameRecGetInsectRecSlot_3ce090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 GameRecGetInsectRecSlot_3ce090(s32 p0, s32 p1)
{
    if (p1 >= 0) {
        if (p1 < 3) {
            goto ok;
        }
    }
    return 0;
ok:
    return ((p0 + (p1 * 0x84C)) + 0x1ADC);
}
