/* rgp:protos */
#define RGP_SELF_ItemDefKindBelow4_40e430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ItemDefKindBelow4_40e430(void *arg0)
{
    s8 x = *(s8 *)((u8 *)arg0 + 0x2);
    if (x == 0 || x == 1 || x == 2) {
        goto one;
    }
    if (x == 3) {
    one:
        return 1;
    }
    return 0;
}
