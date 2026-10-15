#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

extern s32 EquipSlotClearGaugeInBattle_39fd50(void);

u8 EquipSlotClearGaugeInBattleThunk_39f600(void)
{
    return (u8)EquipSlotClearGaugeInBattle_39fd50();
}
