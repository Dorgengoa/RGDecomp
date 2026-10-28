/* rgp:protos */
#define RGP_SELF_NumPutS64_1a4430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void NumPutS64_1a4430(s32 arg0, volatile s32 arg1, void *arg2, s32 arg3, s64 arg4)
{
    s8 sp8F;
    s8 sp60[0x2c] __attribute__((aligned(16)));
    s32 var_16;
    s64 var_8;

    var_8 = arg4;
    var_16 = 0;
    if ((var_8 >= 0) && ((u16)(*(u16 *)((u8 *)arg2 + 0x38) & 0x800))) {
        var_16 = 1;
        sp8F = 0x2B;
    } else if (var_8 < 0) {
        var_16 = 1;
        sp8F = 0x2D;
        var_8 = -var_8;
    }
    NumPutPadOutput_1a4610(arg0, arg1, arg2, arg3, &sp8F, var_16, sp60, NumPutFormatU64_1a4970(arg2, var_8, sp60));
}
