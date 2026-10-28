/* rgp:protos */
#define RGP_SELF_TaskTableRestoreOrder_27bed0 1
#include "port/game_protos.h"
#line 1
#pragma opt_common_subs off
#include "types.h"

/*rgp*/
/*rgp*/
extern u8 D_0044ECF0[0x400];
extern u8 D_004D7FA0[0x400];

void TaskTableRestoreOrder_27bed0(void)
{
    s32 *temp_17;
    s32 *temp_18;
    s32 temp_4;
    s32 var_16;

    for (var_16 = 0; (temp_17 = (s32 *)(D_004D7FA0 + var_16 * 0x10),temp_4 = *temp_17) != 0; var_16++) {
        temp_18 = (s32 *)(D_0044ECF0 + var_16 * 0x10);
        if (((unsigned char)StrEqualNonNull_1ca6c0(temp_4, *temp_18)) == 0) TaskMoveBefore_27bf50(*temp_18, *temp_17);
    }
}
