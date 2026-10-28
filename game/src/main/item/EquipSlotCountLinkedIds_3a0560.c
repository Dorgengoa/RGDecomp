/* rgp:protos */
#define RGP_SELF_EquipSlotCountLinkedIds_3a0560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EquipSlotCountLinkedIds_3a0560(void *rgp_a0)
{
    u8 *base;
    s32 n;
    s32 i;

    base = ((u8 *)EquipSlotGetAbilityKind0Rec_3a0780((void *)rgp_a0));
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
