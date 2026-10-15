#include "types.h"

extern s32 NodeObjCollBoundsOverlap_194480(s32, s32);

s32 MapAreaModelCollectOverlappingNodesMaybe_188c20(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_19;
    s32 temp_20;
    s32 temp_23;
    s32 temp_2;
    s32 var_22;
    s32 var_21;

    if (arg1 == 0) {
        return 0;
    }
    temp_20 = *(s32 *)((u8 *)arg0 + 0x514);
    var_22 = 0;
    temp_23 = *(s32 *)((u8 *)arg0 + 0x518);
    var_21 = 0;
    while (var_21 < temp_20) {
        temp_19 = *(s32 *)((u8 *)(s32)temp_23 + (var_21 * 4));
        if ((temp_19 == 0) || (NodeObjCollBoundsOverlap_194480(temp_19, arg1) == 0) ||
            (temp_2 = var_22 * 4, var_22 += 1, *(s32 *)((u8 *)(s32)arg2 + temp_2) = temp_19, ((var_22 < arg3) != 0))) {
            var_21 += 1;
            continue;
        }
        break;
    }
    return var_22;
}
