/* rgp:protos */
#define RGP_SELF_MapCollectActiveBlocks_1e3e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MapCollectActiveBlocks_1e3e70(s32 arg0, s32 arg1, s32 arg2) {
    s32 p;
    s32 sum;
    s32 i;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    p = arg0 + 0x1928;
    sum = 0;
    i = 0;
    while (i < 4) {
        sum += MapAreaCollectActiveBlocks_1dbb40(p, arg1 + sum * 4, arg2 - sum);
        if (sum >= arg2) {
            break;
        }
        i++;
        p += 0x1CC;
    }
    return sum;
}
