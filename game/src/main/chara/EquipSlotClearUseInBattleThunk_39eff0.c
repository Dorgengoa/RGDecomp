/* rgp:protos */
#define RGP_SELF_EquipSlotClearUseInBattleThunk_39eff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

/*rgp*/

u32 EquipSlotClearUseInBattleThunk_39eff0(int rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    return (u8)((u8)EquipSlotClearUseInBattle_39fdd0((int)rgp_a0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3));
}
