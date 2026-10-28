/* rgp:protos */
#define RGP_SELF_MapFindSmallestBlockAtPos_1e3b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1EC;

void MapFindSmallestBlockAtPos_1e3b50(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, f32 fparg0)
{
    f32 temp_f0;
    f32 var_f20;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_17;
    s32 var_16;

    if ((arg1 != NULL) || (arg2 != NULL)) {
        if (arg1 != NULL) {
            *arg1 = 0;
        }
        if (arg2 != NULL) {
            *arg2 = 0;
        }
        temp_2 = MapGetAreaSlot2_1e5740(arg0);
        if ((temp_2 != 0) && (((unsigned char)MapDataIsEnabled_1e7c20(temp_2)) != 0) && (((unsigned char)MapDataIsLoaded_1e79d0(temp_2)) != 0)) {
            if (arg1 != NULL) {
                *arg1 = temp_2;
            }
            if (arg2 != NULL) {
                *arg2 = temp_2;
            }
            return;
        } else {
            var_f20 = D_0047D1EC;
            var_17 = arg0 + 0x1928;
            var_16 = 0;
            do {
                if (var_16 != 2) {
                    temp_2_2 = MapAreaFindSmallestBlockAt_1db4f0(var_17, arg3, fparg0);
                    if (temp_2_2 != 0) {
                        temp_f0 = MapBlockGetBoxVolume_1dfe80(temp_2_2);
                        if (!(var_f20 <= temp_f0)) {
                            var_f20 = temp_f0;
                            if (arg1 != NULL) {
                                *arg1 = var_17;
                            }
                            if (arg2 != NULL) {
                                *arg2 = temp_2_2;
                            }
                        }
                    }
                }
                var_16 += 1;
                var_17 += 0x1CC;
            } while (var_16 < 4);
        }
    }
}
