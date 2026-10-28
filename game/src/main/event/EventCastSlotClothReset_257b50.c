/* rgp:protos */
#define RGP_SELF_EventCastSlotClothReset_257b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
extern s32 D_00481F78;

s32 EventCastSlotClothReset_257b50(s32 arg0, s32 arg1) {
    s32 var_17;
    void *temp_16;
    void *temp_2;
    void *temp_3;

    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    temp_16 = (void *)(arg0 + (arg1 * 0x10));
    if (*(s32 *)((u8 *)temp_16 + 0) != 0) {
        return 0;
    }
    temp_3 = *(void **)((u8 *)temp_16 + 0xC);
    if (temp_3 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)temp_3 + 0x464) = 1;
    *(s8 *)((u8 *)temp_3 + 0x468) = 0;
    if (*(s32 *)((u8 *)temp_16 + 4) < 4) {
        var_17 = 0;
        do {
            temp_2 = ObjRecGetLiveObject_1c4a90(D_00481F78, var_17 + ((*(s32 *)((u8 *)temp_16 + 4) * 3) + 8));
            if (temp_2 != NULL) {
                *(s32 *)((u8 *)temp_2 + 0x464) = 1;
                *(s8 *)((u8 *)temp_2 + 0x468) = 0;
            }
            var_17 += 1;
        } while (var_17 < 3);
    }
    return 1;
}
