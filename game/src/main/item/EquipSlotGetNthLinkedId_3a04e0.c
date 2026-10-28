/* rgp:protos */
#define RGP_SELF_EquipSlotGetNthLinkedId_3a04e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s16 EquipSlotGetNthLinkedId_3a04e0(void *unused, s32 arg1) {
    void *base;
    s16 result;
    s32 count;
    s32 i;
    s16 val;

    base = (void *)EquipSlotGetAbilityKind0Rec_3a0780((void *)unused);
    if (base == 0) {
        return 0;
    }
    result = -1;
    count = 0;
    for (i = 0; i < 2; i++) {
        val = *(s16 *)((u8 *)base + 8 + i * 2);
        if (val >= 0) {
            if (count == arg1) {
                result = val;
                break;
            } else {
                count++;
            }
        }
    }
    return result;
}
