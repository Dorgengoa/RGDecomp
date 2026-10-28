/* rgp:protos */
#define RGP_SELF_EventAreaListClear_24a280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void EventAreaListClear_24a280(u8 *p)
{
    s32 *q;
    s32  i;

    q = (s32 *)(p + 0x334);
    for (i = 0; i < 0x20; i++) {
        *q = -1;
        q++;
    }
}
