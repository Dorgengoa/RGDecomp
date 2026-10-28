/* rgp:protos */
#define RGP_SELF_AiCmdRouteVarGet_2c69b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_004DB930[];

s32 AiCmdRouteVarGet_2c69b0(s64 *arg0)
{
    u8 *temp_4;

    if (D_004DB930[0] == 0) {
        return 0;
    }
    temp_4 = (u8 *)(ScriptSlotGetInt_2cc9c0(arg0++) * 0xC);
    temp_4 = temp_4 + (s32)D_004DB930[0];
    switch (*(s32 *)(temp_4 + 0xD0)) {
    case 0:
        ScriptSlotStoreIntRef_2cc900(arg0, *(volatile s32 *)(temp_4 + 0xD8));
        break;
    case 1:
        ScriptSlotStoreFloatRef_2cc8e0(arg0, *(volatile f32 *)(temp_4 + 0xD8));
        break;
    }
    return 1;
}
