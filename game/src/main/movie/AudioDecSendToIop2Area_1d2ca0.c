/* rgp:protos */
#define RGP_SELF_AudioDecSendToIop2Area_1d2ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

/*rgp*/

s32 AudioDecSendToIop2Area_1d2ca0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    s32 temp_19;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_2;

    temp_3 = arg5 + arg7;
    temp_2 = arg1 + arg3;
    if (temp_2 < temp_3) {
        temp_3_2 = temp_3 - temp_2;
        if (temp_3_2 >= arg7) {
            arg5 -= temp_3_2 - arg7;
            arg7 = 0;
        } else {
            arg7 -= temp_3_2;
        }
    }
    if (arg5 >= arg1) {
        SifDmaSendSync_1d2c20(arg0, arg4, arg1);
        SifDmaSendSync_1d2c20(arg2, arg4 + arg1, arg5 - arg1);
        SifDmaSendSync_1d2c20((arg2 + arg5) - arg1, arg6, arg7);
    } else {
        if (arg7 >= (arg1 - arg5)) {
            SifDmaSendSync_1d2c20(arg0, arg4, arg5);
            temp_19 = arg1 - arg5;
            SifDmaSendSync_1d2c20(arg0 + arg5, arg6, temp_19);
            SifDmaSendSync_1d2c20(arg2, (arg6 + arg1) - arg5, arg7 - temp_19);
        } else {
            SifDmaSendSync_1d2c20(arg0, arg4, arg5);
            SifDmaSendSync_1d2c20(arg0 + arg5, arg6, arg7);
        }
    }
    return arg5 + arg7;
}
