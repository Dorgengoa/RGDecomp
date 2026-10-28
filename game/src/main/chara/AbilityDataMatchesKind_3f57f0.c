/* rgp:protos */
#define RGP_SELF_AbilityDataMatchesKind_3f57f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                 /* extern */

s32 AbilityDataMatchesKind_3f57f0(void *arg0, s32 arg1) {
    s32 temp_3;
    s32 v;

    if (arg1 < 0 || (temp_3 = *(u8 *)((u8 *)arg0 + 0x2), v = arg1, temp_3 == v)) {
        return 1;
    }
    if (arg1 == 3) {
        if (temp_3 == 0 || AbilityDataGetCompositeId_3f5e10((void *)arg0) == 0x86) {
            return 1;
        }
    }
    return 0;
}
