/* rgp:protos */
#define RGP_SELF_EventIconFindFree_278750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 EventIconFindFree_278750(s32 p0)
{
    s32 l0;
    s32 q;
    s32 t0;
    u8 ok;

    l0 = 0;
    while (l0 < 0x10) {
        q = p0 + (l0 << 6);
        t0 = *(s32 *)(q + 0x28);
        ok = (t0 >= 0);
        if (ok == 0) {
            return q;
        }
        l0 = (l0 + 1);
    }
    return 0;
}
