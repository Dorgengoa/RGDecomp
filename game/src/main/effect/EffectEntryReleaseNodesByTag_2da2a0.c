/* rgp:protos */
#define RGP_SELF_EffectEntryReleaseNodesByTag_2da2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/

void EffectEntryReleaseNodesByTag_2da2a0(void *arg0, s32 arg1) {
    u8 *temp_3;
    u8 *temp_3_2;
    u8 **var_4;
    u8 *temp_5;

    if (*(void **)((u8 *)arg0 + 4) == NULL) {
        *(void **)((u8 *)arg0 + 4) = *(void **)((u8 *)arg0 + 0);
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    for (;;) {
        temp_3 = *(u8 **)((u8 *)arg0 + 4);
        if (temp_3 == NULL) {
            var_4 = NULL;
        } else {
            var_4 = (u8 **)(temp_3 + 0x10);
            temp_3_2 = *(u8 **)temp_3;
            *(void **)((u8 *)arg0 + 4) = temp_3_2;
            if (temp_3_2 == NULL) {
                *(s32 *)((u8 *)arg0 + 8) = 1;
            }
        }
        if (var_4 != NULL) {
            temp_5 = *var_4;
            if (temp_5 != NULL && arg1 == *(s16 *)(temp_5 + 4)) {
                EffectEntryReleaseNode_2da6c0(arg0, temp_5, 0, 0);
            }
            continue;
        }
        break;
    }
    *(void **)((u8 *)arg0 + 4) = NULL;
    *(s32 *)((u8 *)arg0 + 8) = 0;
}
