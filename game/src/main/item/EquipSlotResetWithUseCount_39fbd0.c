/* rgp:protos */
#define RGP_SELF_EquipSlotResetWithUseCount_39fbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T39FBD0 { u8 pad000[0x24]; s16 f24; u8 f26_b : 1; u8 f26_a : 7; };

/*rgp*/

void EquipSlotResetWithUseCount_39fbd0(struct T39FBD0 *p)
{
    EquipSlotReset_3a0910(p);
    p->f24 = 0;
    p->f26_b = 1;
}
