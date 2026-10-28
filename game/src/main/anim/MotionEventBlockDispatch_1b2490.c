/* rgp:protos */
#define RGP_SELF_MotionEventBlockDispatch_1b2490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MotionEventBlockDispatch_1b2490(void *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1) {
    s32 temp_4;
    s32 var_17;
    void *var_16;

    var_17 = 0;
    var_16 = *(void **)((u8 *)arg0 + 0x10);
    while (var_16 != NULL) {
        temp_4 = *(s32 *)((u8 *)var_16 + 0x10);
        if (temp_4 != 0) {
            var_17 += MotionEventCheck_1b1a00(temp_4, arg1, arg2, fparg0, fparg1);
        }
        var_16 = *(void **)((u8 *)var_16 + 0);
    }
    return var_17;
}
