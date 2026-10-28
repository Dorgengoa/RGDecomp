/* rgp:protos */
#define RGP_SELF_MotionEventEffectWriteText_1b1470 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 2
#pragma schedule on
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045A9B0[0x400];
extern u8 D_0045A9B8[0x400];
extern u8 D_0045A9C8[0x400];
extern u8 D_0045A9D0[0x400];
extern u8 D_0045A9D8[0x400];
extern u8 D_0045A9E0[0x400];
extern u8 D_0045A9E8[0x400];

void MotionEventEffectWriteText_1b1470(void *arg0, s32 arg1)
{
    s32 arg_h1;
    void *u;

    void *temp_17;
    void *temp_16;
    arg_h1 = arg1;
    MotionEventWriteHeaderText_1b1850((void *)arg0, &(*(u8 *)D_0045A9B0), arg_h1);
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9B8));
    temp_17 = *(void **)((u8 *)arg0 + 0x28);
    temp_16 = *(void **)((u8 *)arg0 + 0x2C);
    if (temp_17 == NULL) {
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9C8));
    } else {
        OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9D0))), temp_17)), &(*(u8 *)D_0045A9D0));
    }
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9D8));
    if (temp_16 == NULL) {
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9C8));
    } else {
        OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9D0))), temp_16)), &(*(u8 *)D_0045A9D0));
    }
    OstreamWriteBool_1b2710(((s32)OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9D8))), *((u8 *)arg0 + 0x34));
    OstreamWriteBool_1b2710(((s32)OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9D8))), *((u8 *)arg0 + 0x35));
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9E0));
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, &(*(u8 *)D_0045A9E8));
}
