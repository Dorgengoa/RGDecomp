/* rgp:protos */
#define RGP_SELF_AiCmdSetContactRollOffMaybe_2c45c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s8 *D_004DB930[3];

s32 AiCmdSetContactRollOffMaybe_2c45c0(s32 a0)
{
    D_004DB930[0][0x16C] = ScriptSlotGetInt_2cc9c0(a0);
    return 1;
}
