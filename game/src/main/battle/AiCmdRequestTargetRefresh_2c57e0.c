/* rgp:protos */
#define RGP_SELF_AiCmdRequestTargetRefresh_2c57e0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK: 3 rounds tried (0-arg BattleAiRequestTargetRefresh_2cedc0 w/ late arg0+8; BattleAiRequestTargetRefresh_2cedc0(arg0)
   w/ late arg0+8; 0-arg BattleAiRequestTargetRefresh_2cedc0 w/ EARLY temp_16=arg0+8 fold matching
   retail's daddu-in-delay-slot). All three land at 0x80 vs retail's 0x88
   (8 bytes / 2 words short) with identical bad-word behavior otherwise --
   the missing 2 words are elsewhere in the branch shape, not the arg0+8
   fold. Not re-tried further. */
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB930[0x400];

s32 AiCmdRequestTargetRefresh_2c57e0(s32 arg0)
{
    s32 temp_16;
    s32 temp_2;
    s32 temp_4;

    temp_16 = arg0;
    temp_4 = temp_16;
    temp_16 += 8;
    temp_2 = ScriptSlotGetInt_2cc9c0(temp_4);
    switch (temp_2) {
    case 0:
        BattleAiRequestTargetRefresh_2cedc0();
        break;
    case 1:
        BattleAiRequestTargetRefresh_2cedc0();
        *(u8 *)((u8 *)(*(void * *)D_004DB930) + 0x171) = 1;
        break;
    default:
        BattleAiRequestTargetRefresh_2cedc0();
        break;
    }
    ScriptSlotStoreIntRef_2cc900(temp_16, -1);
    return 1;
}
