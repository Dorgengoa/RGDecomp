/* rgp:protos */
#define RGP_SELF_TreasureBoxIsLockedMaybe_33acf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/

s32 TreasureBoxIsLockedMaybe_33acf0(void *arg0) {
    s16 v;

    if (*(void **)((u8 *)arg0 + 0x68) == NULL) {
        return 0;
    }
    if (TreasureBoxIsOpened_33a240(arg0) != 0) {
        return 0;
    }
    v = *(s16 *)(*(u8 **)((u32)arg0 + 0x68) + 0xC);
    if (v == 1 || v == 2 || v == 3) {
        return 1;
    }
    return 0;
}
