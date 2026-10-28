/* rgp:protos */
#define RGP_SELF_BtlChgMenuIsMemberPageUp_204e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 BtlChgMenuIsMemberPageUp_204e20(void)
{
    s32 r;

    r = 1;
    if (func_4F9D40() != 2) {
        r = 0;
    }
    return r;
}
