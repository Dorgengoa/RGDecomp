/* rgp:protos */
#define RGP_SELF_SysParamTableLoadDefaults_1c6b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044B020[0x400];
extern u8 D_0044B270[0x400];
extern u8 D_004B2C80[0x400];

void SysParamTableLoadDefaults_1c6b20(void)
{
    s32 temp_5;
    s32 temp_5_2;
    s32 i;
    s32 j;
    u8 *cur;

    SysParamTableClear_15ff30(&(*(u8 *)D_004B2C80));
    i = 0;
    while ((temp_5 = *(s32 *)(&(*(u8 *)D_0044B020) + i * 4)) >= 0) {
        cur = &(*(u8 *)D_0044B020) + i * 4;
        SysParamTableSetInt_15fef0(&(*(u8 *)D_004B2C80), temp_5, *(s32 *)(cur + 0x8), *(s32 *)(cur + 0x4));
        i += 3;
    }
    j = 0;
    while ((temp_5_2 = *(s32 *)(&(*(u8 *)D_0044B270) + j * 4)) >= 0) {
        SysParamTableSetFloat_15feb0(&(*(u8 *)D_004B2C80), temp_5_2, *(s32 *)(&(*(u8 *)D_0044B270) + j * 4 + 0x4));
        j += 2;
    }
}
