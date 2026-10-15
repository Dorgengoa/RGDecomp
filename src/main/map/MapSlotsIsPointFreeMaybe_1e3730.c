#include "types.h"

extern s32 MapAreaIsPointFreeMaybe_1db0e0(s32, s32, f32);
extern s32 MapGetAreaSlot2_1e5740(void);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapDataIsEnabled_1e7c20(s32);

s32 MapSlotsIsPointFreeMaybe_1e3730(s32 arg0, s32 arg1, f32 fparg0) {
    s32 temp_2;
    s32 var_17;
    s32 var_16;

    temp_2 = MapGetAreaSlot2_1e5740();
    if ((temp_2 != 0) && (MapDataIsEnabled_1e7c20(temp_2) != 0) && (MapDataIsLoaded_1e79d0(temp_2) != 0)) {
        return MapAreaIsPointFreeMaybe_1db0e0(temp_2, arg1, fparg0);
    }
    var_17 = arg0 + 0x1928;
    var_16 = 0;
    while (var_16 < 4) {
        if ((var_16 != 2) && (MapAreaIsPointFreeMaybe_1db0e0(var_17, arg1, fparg0) == 0)) {
            return 0;
        }
        var_16 += 1;
        var_17 += 0x1CC;
    }
    return 1;
}
