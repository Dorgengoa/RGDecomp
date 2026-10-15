#include "types.h"

u8 InvCategoryMatches_3c8720(s32 arg0, s32 arg1, u32 arg2) {
    u8 var_2;

    var_2 = 0;
    if (arg1 == -1) {
        var_2 = 1;
    } else if (arg1 == 10) {
        if (arg2 < 2U) {
            var_2 = 1;
        }
    } else if (arg1 == 0 || arg1 == 1 || arg1 == 2 || arg1 == 3 || arg1 == 4 ||
               arg1 == 5 || arg1 == 6 || arg1 == 7 || arg1 == 9) {
        if (arg1 == (s32)arg2) {
            var_2 = 1;
        }
    }
    return var_2;
}
