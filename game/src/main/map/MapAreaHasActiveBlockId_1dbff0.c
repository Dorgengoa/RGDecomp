/* rgp:protos */
#define RGP_SELF_MapAreaHasActiveBlockId_1dbff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapAreaHasActiveBlockId_1dbff0(void *arg0, s32 arg1) {
    s32 *var_19;
    s32 var_18;

    if (((unsigned char)MapDataIsLoaded_1e79d0((int)arg0)) == 0) {
        return 0;
    }
    if ((arg1 < ((short)MapIdIndexGetMinId_1ddbe0((s32 *)((u8 *)arg0 + 0x10C)))) || (((short)MapIdIndexGetMaxId_1ddbf0((s32 *)((u8 *)arg0 + 0x10C))) < arg1)) return 0;
    var_19 = (s32 *)((u8 *)arg0 + 0x178);
    var_18 = 0;
    while (var_18 < *(s16 *)((u8 *)arg0 + 0x1CA)) {
        if (arg1 == ((short)MapDataGetId_1e7bd0(*var_19))) {
            return 1;
        }
        var_18 += 1;
        var_19 += 1;
    }
    return 0;
}
