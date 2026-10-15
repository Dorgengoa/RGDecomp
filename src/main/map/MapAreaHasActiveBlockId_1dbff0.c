#include "types.h"
#pragma opt_common_subs off

extern s32 MapIdIndexGetMinId_1ddbe0(s32 *);
extern s32 MapIdIndexGetMaxId_1ddbf0(s32 *);
extern s32 MapDataIsLoaded_1e79d0(void);
extern s32 MapDataGetId_1e7bd0(s32);

s32 MapAreaHasActiveBlockId_1dbff0(void *arg0, s32 arg1) {
    s32 *var_19;
    s32 var_18;

    if (MapDataIsLoaded_1e79d0() == 0) {
        return 0;
    }
    if ((arg1 < MapIdIndexGetMinId_1ddbe0((s32 *)((u8 *)arg0 + 0x10C))) || (MapIdIndexGetMaxId_1ddbf0((s32 *)((u8 *)arg0 + 0x10C)) < arg1)) return 0;
    var_19 = (s32 *)((u8 *)arg0 + 0x178);
    var_18 = 0;
    while (var_18 < *(s16 *)((u8 *)arg0 + 0x1CA)) {
        if (arg1 == MapDataGetId_1e7bd0(*var_19)) {
            return 1;
        }
        var_18 += 1;
        var_19 += 1;
    }
    return 0;
}
