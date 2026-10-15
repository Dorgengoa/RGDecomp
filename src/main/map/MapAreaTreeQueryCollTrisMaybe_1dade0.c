/* MATCH (s41m). Stale pre-match note follows -- PARK: same length as retail, 59 bad words after 1 round (passed NULL for
   the first MapDataIsLoaded_1e79d0() call's dropped arg -- likely wrong, see the
   empty-paren-call lever noted elsewhere in this report). Not re-tried. */
#include "types.h"

extern s32 MapDataQueryCollTrisMaybe_1e6bc0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 MapDataIsLoaded_1e79d0(void *arg0);
extern s32 MapDataQueryCollTrisThunkMaybe_1e6bc0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 MapAreaTreeQueryCollTrisMaybe_1dade0(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
        s32 arg_h2;

    s32 var_17;
    s32 var_22;
    s32 var_22_2;
    void **var_16;
    void **var_16_2;

    if ((arg1 == 0) || (arg2 <= 0)) {
        return 0;
    }
    if (!(MapDataIsLoaded_1e79d0(arg0) != 0)) {
        return 0;
    }
    arg_h2 = arg2;
    var_17 = MapDataQueryCollTrisMaybe_1e6bc0(arg0, arg1, arg_h2, arg3);
    var_16 = (void **)((u8 *)arg0 + 0x128);
    var_22 = 0;
    while (var_22 < *(s16 *)((u8 *)arg0 + 0x1C8)) {
        if ((MapDataIsLoaded_1e79d0(*var_16) == 0) ||
            (var_17 += MapDataQueryCollTrisMaybe_1e6bc0(*var_16, arg1 + (var_17 * 0x60), arg2 - var_17, arg3), (var_17 < arg2))) {
            var_22 += 1;
            var_16 += 1;
            continue;
        }
        break;
    }
    var_16_2 = (void **)((u8 *)arg0 + 0x178);
    var_22_2 = 0;
    while (var_22_2 < *(s16 *)((u8 *)arg0 + 0x1CA)) {
        if ((MapDataIsLoaded_1e79d0(*var_16_2) == 0) ||
            (var_17 += MapDataQueryCollTrisThunkMaybe_1e6bc0(*var_16_2, arg1 + (var_17 * 0x60), arg2 - var_17, arg3), (var_17 < arg2))) {
            var_22_2 += 1;
            var_16_2 += 1;
            continue;
        }
        break;
    }
    return var_17;
    return 0;
}
