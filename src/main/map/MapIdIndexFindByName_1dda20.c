#include "types.h"

extern s32 MapDataGetName_1e7bf0(s32);
extern s32 strcmp(s32, s32);

s32 MapIdIndexFindByName_1dda20(void *arg0, s32 arg1) {
    s32 var_17;
    s32 temp_20;
    s32 temp_2;
    s32 temp_3;
    s32 var_16;

    if (arg1 == 0) {
        return 0;
    }
    var_17 = *(s16 *)((u8 *)arg0 + 0xC);
    var_16 = 0;
    do {
        var_17 = var_17 >> 1;
        temp_3 = var_16 + var_17;
        if (temp_3 < *(s16 *)((u8 *)arg0 + 0xE)) {
            temp_20 = *(s32 *)(*(u8 **)((u8 *)arg0 + 4) + temp_3 * 4);
            if (MapDataGetName_1e7bf0(temp_20) != 0) {
                temp_2 = strcmp(arg1, MapDataGetName_1e7bf0(temp_20));
                if (temp_2 == 0) {
                    return temp_20;
                }
                if (temp_2 > 0) {
                    var_16 += var_17;
                }
            }
        }
    } while (var_17 > 0);
    return 0;
}
