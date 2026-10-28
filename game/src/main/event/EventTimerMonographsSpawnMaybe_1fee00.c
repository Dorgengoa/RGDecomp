/* rgp:protos */
#define RGP_SELF_EventTimerMonographsSpawnMaybe_1fee00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern void Sprintf_1343b8(void *, void *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B078[0x400];
extern u8 D_0045BFE0[0x400];
extern u8 D_0045BFE8[0x400];

s32 EventTimerMonographsSpawnMaybe_1fee00(void)
{
    s32 arg_h1;

    u8 sp50[0x10] __attribute__((aligned(16)));
    s32 temp_19;
    s32 temp_2;
    s32 temp_f0;
    s32 var_16;
    void *temp_2_2;

    temp_2 = MapSlotsFindIdByName_1e4520(((s32)GetMapMgr_201a90()), &(*(u8 *)D_0045BFE0));
    if (temp_2 <= 0) {
        return 0;
    }
    temp_2_2 = GetGameData_1fede0();
    arg_h1 = 0x2D;
    if (!(StateFlagTest_3ccd70(*(s32 *)((u8 *)temp_2_2 + 0x10), arg_h1) & 0xFF)) {
        return 0;
    }
    temp_f0 = (s32)(30.0f * ((*(f32 *)((u8 *)(*(u8 **)((u8 *)temp_2_2 + 0x18)) + 0x4C64) / (*(f32 *)D_0045B078)) - 6.0f));
    if (temp_f0 <= 0) {
        StateFlagSet_3ccb70(*(s32 *)((u8 *)temp_2_2 + 0x10), 0x2D, 0, 0);
        EventTimerClear_3c06d0(*(u8 **)((u8 *)temp_2_2 + 0x18), 1);
    } else {
        temp_19 = ((s32)GetEventObjMgr_2d1960());
        var_16 = 1;
        do {
            Sprintf_1343b8(sp50, &(*(u8 *)D_0045BFE8), var_16);
            EvSpawnMonograph_2e90f0(temp_19, temp_2, sp50, (f32)temp_f0, -1.0f);
            var_16 += 1;
        } while (var_16 <= 0x16);
    }
    return 1;
    return 0;
}
