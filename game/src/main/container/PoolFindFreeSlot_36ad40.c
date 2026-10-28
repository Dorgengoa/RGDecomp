/* rgp:protos */
#define RGP_SELF_PoolFindFreeSlot_36ad40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
s32 PoolFindFreeSlot_36ad40(void *arg0) {
    s32 bound;
    s32 word;
    s32 found;
    s32 *arr;
    s32 i;
    s32 bit;
    s32 j;

    arr = *(s32 **)((u8 *)arg0 + 0x20);
    found = -1;
    bound = *(s32 *)((u8 *)arg0 + 0x14);
    i = 0;
    while (i < bound && found < 0) {
        word = *arr;
        if (word != -1) {
            bit = 1;
            for (j = 0; j < 0x20 && i < bound; j++) {
                if (word & bit) {
                    bit <<= 1;
                    i++;
                } else {
                    found = i;
                    break;
                }
            }
            if (i >= bound) {
                break;
            }
            if (found >= 0) {
                break;
            }
        } else {
            i += 0x20;
        }

        arr++;
    }
    return found;
}
