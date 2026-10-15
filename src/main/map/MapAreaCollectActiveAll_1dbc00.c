#include "types.h"

extern s32 MapDataIsLoadedOrUnloading_1e7980(void);
extern s32 MapAreaCollectActiveBlocks_1dbb40(s32 arg0, s32 *arg1, s32 arg2);
extern s32 MapAreaCollectActiveShares_1dba80(s32 arg0, s32 *arg1, s32 arg2);

s32 MapAreaCollectActiveAll_1dbc00(s32 arg0, s32 *arg1, s32 arg2) {
    s32 n;
    if (arg1 == NULL || arg2 <= 0) {
        return 0;
    }
    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return 0;
    }
    n = 0;
    *arg1 = arg0;
    n++;
    n += MapAreaCollectActiveBlocks_1dbb40(arg0, arg1 + 1, arg2 - 1);
    return n + MapAreaCollectActiveShares_1dba80(arg0, arg1 + n, arg2 - n);
}
