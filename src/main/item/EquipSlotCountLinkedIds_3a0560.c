#include "types.h"

extern u8 *EquipSlotGetAbilityKind0Rec_3a0780(void);

s32 EquipSlotCountLinkedIds_3a0560(void)
{
    u8 *base;
    s32 n;
    s32 i;

    base = EquipSlotGetAbilityKind0Rec_3a0780();
    if (base != 0) goto ok;
    return 0;
ok:
    n = 0;
    for (i = 0; i < 2; i++) {
        if (*(s16 *)(base + i * 2 + 8) >= 0) {
            n++;
        }
    }
    return n;
}
