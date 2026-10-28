/* rgp:protos */
#define RGP_SELF_AiCmdGetRolledActionMaybe_2c4b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 *D_004DB930[3];
/*rgp*/

s32 AiCmdGetRolledActionMaybe_2c4b20(s32 a0)
{
    ScriptSlotStoreIntRef_2cc900(a0, *(s16 *)(D_004DB930[0] + 0x172));
    return 1;
}
