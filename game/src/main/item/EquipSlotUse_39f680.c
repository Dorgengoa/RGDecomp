/* rgp:protos */
#define RGP_SELF_EquipSlotUse_39f680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S39f680 { u8 pad000[0x24]; s16 m24; };

/*rgp*/

s32 EquipSlotUse_39f680(struct S39f680 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (EquipSlotUseRefillGauge_3a0070(p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3) == 0) {
        return 0;
    }
    p->m24 = p->m24 + 1;
    return 1;
}
