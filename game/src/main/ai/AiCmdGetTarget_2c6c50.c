/* rgp:protos */
#define RGP_SELF_AiCmdGetTarget_2c6c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 *D_004DB930[3];
/*rgp*/

s32 AiCmdGetTarget_2c6c50(s32 a0)
{
    u8 *g;

    g = D_004DB930[0];
    if (g == 0) {
        return 0;
    }
    ScriptSlotStoreIntRef_2cc900(a0, *(s16 *)(g + 0x13C));
    return 1;
}
