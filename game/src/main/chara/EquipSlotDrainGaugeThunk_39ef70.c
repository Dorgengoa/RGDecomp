/* rgp:protos */
#define RGP_SELF_EquipSlotDrainGaugeThunk_39ef70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EquipSlotInBattleThunk_39ef90 (byte-identical, in cunits):
   call the worker and truncate its result to u8. */

/*rgp*/

u32 EquipSlotDrainGaugeThunk_39ef70(void *rgp_a0, float rgp_f0)
{
    return (u8)((u8)EquipSlotDrainGauge_39fc20((void *)rgp_a0, (float)rgp_f0));
}
