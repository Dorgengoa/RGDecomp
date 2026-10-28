/* rgp:protos */
#define RGP_SELF_MapCollectActiveAll_1e3f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MapCollectActiveAll_1e3f10(s32 p0, s32 p1, s32 p2)
{
    s32 l2;
    s32 l1;
    s32 l0;
    s32 r3;

    if (p1 != 0) {
        if (p2 > 0) {
            goto ok;
        }
    }
    return 0;
ok:
    l2 = (p0 + 0x1928);
    l1 = 0;
    l0 = 0;
    while (l0 < 4) {
        r3 = MapAreaCollectActiveAll_1dbc00(l2, (p1 + (l1 << 2)), (p2 - l1));
        l1 = (l1 + r3);
        if (l1 >= p2) {
            return l1;
        }
        l0 = (l0 + 1);
        l2 = (l2 + 0x1CC);
    }
    return l1;
}
