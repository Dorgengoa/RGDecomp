/* rgp:protos */
#define RGP_SELF_LoadHandleNameMatch_28b1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u8 LoadHandleNameMatch_28b1c0(u8 *a, void *b)
{
    s32 r;

    if (b == 0) {
        return 0;
    }
    r = StrNotEqual_1f5300(b, a + 8);
    return (r != 0) ^ 1;
}
