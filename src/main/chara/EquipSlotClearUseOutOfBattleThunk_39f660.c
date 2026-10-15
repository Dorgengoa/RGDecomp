#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

extern s32 EquipSlotClearUseOutOfBattle_39fe20(void);

u8 EquipSlotClearUseOutOfBattleThunk_39f660(void)
{
    return (u8)EquipSlotClearUseOutOfBattle_39fe20();
}
