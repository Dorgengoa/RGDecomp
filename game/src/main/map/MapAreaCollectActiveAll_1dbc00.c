/* rgp:protos */
#define RGP_SELF_MapAreaCollectActiveAll_1dbc00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapAreaCollectActiveAll_1dbc00(s32 arg0, s32 *arg1, s32 arg2) {
    s32 n;
    if (arg1 == NULL || arg2 <= 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)arg0)) == 0) {
        return 0;
    }
    n = 0;
    *arg1 = arg0;
    n++;
    n += MapAreaCollectActiveBlocks_1dbb40(arg0, arg1 + 1, arg2 - 1);
    return n + MapAreaCollectActiveShares_1dba80(arg0, arg1 + n, arg2 - n);
}
