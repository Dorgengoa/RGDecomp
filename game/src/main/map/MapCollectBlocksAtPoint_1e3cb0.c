/* rgp:protos */
#define RGP_SELF_MapCollectBlocksAtPoint_1e3cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MapCollectBlocksAtPoint_1e3cb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0)
{
    s32 base;
    s32 total;
    s32 i;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    base = arg0 + 0x1928;
    total = 0;
    for (i = 0; i < 4; i++, base += 0x1CC) {
        total += MapAreaCollectBlocksAtPoint_1db7e0(base, arg1 + (total * 4), arg2 - total, arg3, fparg0);
        if (total >= arg2) {
            break;
        }
    }
    return total;
}
