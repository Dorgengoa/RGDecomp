#include "types.h"

struct S39f680 { u8 pad000[0x24]; s16 m24; };

extern s32 EquipSlotUseRefillGauge_3a0070(struct S39f680 *);

s32 EquipSlotUse_39f680(struct S39f680 *p)
{
    if (EquipSlotUseRefillGauge_3a0070(p) == 0) {
        return 0;
    }
    p->m24 = p->m24 + 1;
    return 1;
}
