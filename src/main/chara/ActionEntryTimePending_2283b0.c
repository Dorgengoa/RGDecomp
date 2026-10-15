/* main s27m: CLOSED -- both float compares MIRRORED so the literal takes the first
   c.X.s slot: `0.0f <= temp_f2`, `!(1.0f < temp_f1)`. */
#include "types.h"

s32 ActionEntryTimePending_2283b0(void *arg0, f32 fparg0) {
    f32 temp_f2;
    f32 temp_f1;
    s32 var_2;
    s32 var_2_2;
    s32 var_2_3;
    s32 var_3;

    temp_f2 = *(f32 *)((u8 *)arg0 + 4);
    if ((0.0f <= temp_f2) && (fparg0 < temp_f2)) {
        var_3 = 0;
    } else {
        temp_f1 = *(f32 *)((u8 *)arg0 + 8);
        if (!(1.0f < temp_f1) && !(fparg0 <= temp_f1)) {
            var_3 = 0;
        } else {
            var_2_2 = 1;
            if (!(temp_f2 <= temp_f1)) {
                var_2_2 = 0;
            }
            var_3 = var_2_2 & 0xFF;
        }
    }
    var_2 = var_3 & 0xFF;
    if (var_3 != 0) {
        var_2_3 = 1;
        if (*(f32 *)((u8 *)arg0 + 0) <= fparg0) {
            var_2_3 = 0;
        }
        var_2 = var_2_3 & 0xFF;
    }
    return var_2;
}
