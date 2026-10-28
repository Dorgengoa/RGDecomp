/* rgp:protos */
#define RGP_SELF_MapAreaCollectBlocksAtPoint_1db7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;

s32 MapAreaCollectBlocksAtPoint_1db7e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0)
{
    s32 temp_2;
    s32 var_16;
    s32 var_22;
    s32 var_21;

    if (((unsigned char)MapDataIsEnabled_1e7c20((void *)arg0)) == 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(arg0)) == 0) {
        return 0;
    }
    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    var_16 = MapAreaGetPartTables_1dce00(arg0);
    if (var_16 == 0) {
        return 0;
    }
    temp_2 = MapAreaGetPartTableCount_1dcdf0(arg0);
    if (temp_2 <= 0) {
        return 0;
    }
    if (fparg0 < D_0047D5D0) {
        fparg0 = D_0047D5D0;
    }
    var_22 = 0;
    var_21 = 0;
    while (var_21 < temp_2) {
        var_22 += MapPartTableCollectAtPoint_1ddf10(var_16, arg1 + (var_22 * 4), arg2 - var_22, arg3, fparg0);
        if (var_22 >= arg2) {
            break;
        }
        var_21 += 1;
        var_16 += 0x3C;
    }
    return var_22;
}
