/* rgp:protos */
#define RGP_SELF_VariantPoolTrimScope_3d9f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off

/*rgp*/

typedef struct {
    u8 pad0[0xe08];
    s16 unkE08;
    s16 unkE0A;
} T3d9f40_arg0;

s32 VariantPoolTrimScope_3d9f40(T3d9f40_arg0 *arg0) {
    s32 var_5;
    s32 var_7;
    s32 var_9;
    void *temp_2;
    void *temp_6;
    void *var_6;
    void *var_8;

    var_8 = NULL;
    var_5 = 0;
    var_9 = arg0->unkE08 - 1;
    var_7 = var_9;
    for (; var_7 >= 0; var_7--) {
        temp_2 = (u8 *)arg0 + (var_7 * 0x38);
        temp_6 = (u8 *)temp_2 + 8;
        if (arg0->unkE0A == *(s16 *)((u8 *)temp_2 + 0x38)) {
            var_9 = var_7;
            if (*(s32 *)((u8 *)temp_6 + 0x10) != 0) {
                var_8 = temp_6;
            }
            break;
        }
        var_5 += 1;
    }
    arg0->unkE08 = (s16)(var_9 + 1);
    if (var_8 != NULL) {
        var_6 = NULL;
        if (var_5 > 0) {
            var_6 = (u8 *)arg0 + (arg0->unkE08 * 0x38) + 8;
        }
        VariantFireGetCallbackOnce_36e4c0(var_8, var_5, var_6);
    }
    return 0;
}
