/* rgp:protos */
#define RGP_SELF_TargetRefIsValid_2e6e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 TargetRefIsValid_2e6e40(void *arg0) {
    s32 temp_2;
    s32 temp_2_2;

    temp_2 = ((short)TargetRefGetKind_2e7130(arg0));
    switch (temp_2) {
    case 1:
    case 13:
        return 1;
    }
    if (!(*(s32 *)((u8 *)arg0 + 4) != 0)) {
        return 0;
    }
    temp_2_2 = ((short)TargetRefGetKind_2e7130(arg0));
    if ((temp_2_2 != 9) && (temp_2_2 != 8) && (temp_2_2 != 7) && (temp_2_2 != 6)) {
        return 1;
    }
    return MapSlotsFindActiveById_1e4870(((s32)GetMapMgr_201a90()), *(s16 *)((u8 *)arg0 + 2), 0) != 0;
    return 0;
}
