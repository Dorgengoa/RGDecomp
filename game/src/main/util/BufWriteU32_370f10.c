/* rgp:protos */
#define RGP_SELF_BufWriteU32_370f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 BufWriteU32_370f10(s32 *a, s32 b, s32 c)
{
    s32 r;
    if (a == 0) goto zero;
    if (b > 0) goto ok;
zero:
    return 0;
ok:
    r = 4;
    if (b >= 4) {
        *a = c;
    } else {
        r = 0;
    }
    return r;
}
