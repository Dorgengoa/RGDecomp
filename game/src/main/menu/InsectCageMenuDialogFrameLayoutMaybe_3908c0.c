/* rgp:protos */
#define RGP_SELF_InsectCageMenuDialogFrameLayoutMaybe_3908c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void InsectCageMenuDialogFrameLayoutMaybe_3908c0(void *arg0, s32 arg1, s64 arg2, s64 arg3) {
    s16 temp_5;
    s32 var_8;
    s32 var_9;
    u8 *temp_7;

    if (arg0 != NULL) {
        var_8 = arg1 - (*(s16 *)((u8 *)arg0 + 0xC) + *(s16 *)((u8 *)arg0 + 0x4C));
        if (var_8 <= 0) {
            var_8 = 0;
        }
        *(s16 *)((u8 *)arg0 + 0x24) = var_8;
        *(s16*)((u8 *)arg0 + 0x0) = 4;
        var_9 = 0;
        temp_5 = *(s16 *)((u8 *)arg0 + 4);
        *(s16 *)((u8 *)arg0 + 0x20) = temp_5;
        *(s16*)((u8 *)arg0 + 0x40) = (s16)((temp_5 + var_8) - 4);
        do {
            temp_7 = (u8 *)arg0 + (var_9 << 5);
            var_9 += 1;
            *(s16*)(temp_7 + 0x0) += (s16)arg2;
            *(s16*)(temp_7 + 0x2) += (s16)arg3;
        } while (var_9 < 3);
    }
}
