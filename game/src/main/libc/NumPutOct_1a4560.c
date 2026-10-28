/* rgp:protos */
#define RGP_SELF_NumPutOct_1a4560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void NumPutOct_1a4560(s32 arg0, volatile s32 arg1, void *arg2, s32 arg3, s32 arg4)
{
    u8 sp60[0x2F] __attribute__((aligned(16)));
    u8 sp8F;
    s32 var_16;
    u8 *var_6;
    u16 flag;

    var_16 = 0;
    var_6 = sp60;
    if (arg4 == 0 || (flag = *(u16 *)((u8 *)arg2 + 0x38) & 0x200)) {
        *var_6++ = 0x30;
        var_16 += 1;
    }
    if (arg4 != 0) {
        var_16 += NumPutFormatU64_1a4970(arg2, (unsigned long long)(arg4), var_6);
    }
    NumPutPadOutput_1a4610(arg0, arg1, arg2, arg3, &sp8F, 0, sp60, var_16);
}
