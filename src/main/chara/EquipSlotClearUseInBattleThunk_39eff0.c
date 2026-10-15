#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

extern s32 EquipSlotClearUseInBattle_39fdd0(void);

u8 EquipSlotClearUseInBattleThunk_39eff0(void)
{
    return (u8)EquipSlotClearUseInBattle_39fdd0();
}
