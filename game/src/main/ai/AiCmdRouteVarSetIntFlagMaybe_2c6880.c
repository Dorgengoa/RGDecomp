/* rgp:protos */
#define RGP_SELF_AiCmdRouteVarSetIntFlagMaybe_2c6880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_004DB930[0x400];

s32 AiCmdRouteVarSetIntFlagMaybe_2c6880(s64 *arg0, s32 arg1) {
    u32 temp_16;
    s32 var_2;
    void *temp_3;

    if ((*(s32 *)D_004DB930) == 0) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    var_2 = 0;
    if (arg1 >= 2) {
        var_2 = ScriptSlotGetInt_2cc9c0((s32)arg0);
    }
    { s32 b_ = *(volatile s32 *)D_004DB930; temp_3 = (void *)(temp_16 * 0xC); temp_3 = (u8 *)temp_3 + b_; }
    *(s32 *)((u8 *)temp_3 + 0xD0) = 0;
    *(s32 *)((u8 *)temp_3 + 0xD8) = var_2;
    *(s32 *)((u8 *)temp_3 + 0xD4) = 1;
    return 1;
}
