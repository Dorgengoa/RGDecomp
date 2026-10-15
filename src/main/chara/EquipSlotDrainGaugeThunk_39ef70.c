#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

extern s32 EquipSlotDrainGauge_39fc20(void);

u8 EquipSlotDrainGaugeThunk_39ef70(void)
{
    return (u8)EquipSlotDrainGauge_39fc20();
}
