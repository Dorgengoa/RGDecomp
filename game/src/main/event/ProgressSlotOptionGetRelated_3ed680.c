/* rgp:protos */
#define RGP_SELF_ProgressSlotOptionGetRelated_3ed680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/                               /* extern */

s32 ProgressSlotOptionGetRelated_3ed680(void *arg0, s32 arg1) {
    s32 v;
    void *t;

    t = PlanetAreaMatrixLookupByProgress_3ed840((void *)arg0, (int)arg1);
    if (t == NULL) {
        return 0;
    }
    if (arg1 == 0xA) {
        return 0;
    }
    v = *(s16 *)((u8 *)t + 0x28);
    if (arg1 == 6) {
        if (v == 1) {
            if (StateFlagTest_3ccd70(*(s32 *)((u8 *)arg0 + 0x10), 0xA3) == 0) {
                v = 0;
            }
        }
    } else if (arg1 == 7) {
        if (((short)StateVarGet_3ccac0(*(s32 *)((u8 *)arg0 + 0x10), 0xD)) <= 0) {
            v = 0;
        }
    } else if (arg1 == 0x15) {
        if (((short)StateVarGet_3ccac0(*(s32 *)((u8 *)arg0 + 0x10), 2)) <= 0) {
            v = 0;
        }
    }
    return v;
}
