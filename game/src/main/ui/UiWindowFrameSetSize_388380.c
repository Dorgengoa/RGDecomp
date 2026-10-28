/* rgp:protos */
#define RGP_SELF_UiWindowFrameSetSize_388380 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
extern s32 D_00483308;

void UiWindowFrameSetSize_388380(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_5;
    s32 temp_5_2;

    if (D_00483308 == 0 || arg0 == NULL) {
        return;
    }
    {
        {
        *(s16 *)((u8 *)arg0 + 4) = arg1 - 8;
        *(s16 *)((u8 *)arg0 + 6) = arg2 - 8;
        temp_5 = arg1 - (*(s16 *)((u8 *)arg0 + 0x2C) + *(s16 *)((u8 *)arg0 + 0x6C));
        *(s16 *)((u8 *)arg0 + 0x44) = temp_5;
        *(s16 *)((u8 *)arg0 + 0x60) = *(s16 *)((u8 *)arg0 + 0x40) + temp_5;
        *(s16 *)((u8 *)arg0 + 0xE4) = temp_5;
        *(s16 *)((u8 *)arg0 + 0x100) = *(s16 *)((u8 *)arg0 + 0xE0) + temp_5;
        *(s16 *)((u8 *)arg0 + 0xA0) = *(s16 *)((u8 *)arg0 + 0xE0) + temp_5 + 5;
        temp_5_2 = arg2 - (*(s16 *)((u8 *)arg0 + 0x2E) + *(s16 *)((u8 *)arg0 + 0xCE));
        *(s16 *)((u8 *)arg0 + 0x86) = temp_5_2;
        *(s16 *)((u8 *)arg0 + 0xC2) = *(s16 *)((u8 *)arg0 + 0x82) + temp_5_2;
        *(s16 *)((u8 *)arg0 + 0xA6) = temp_5_2;
        *(s16 *)((u8 *)arg0 + 0x102) = *(s16 *)((u8 *)arg0 + 0xA2) + temp_5_2;
        *(s16 *)((u8 *)arg0 + 0xE2) = *(s16 *)((u8 *)arg0 + 0xA2) + temp_5_2;
        }
    }
}
