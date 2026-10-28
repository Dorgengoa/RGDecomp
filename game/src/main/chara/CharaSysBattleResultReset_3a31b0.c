/* rgp:protos */
#define RGP_SELF_CharaSysBattleResultReset_3a31b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg0_003a31b0 {
    u8 pad0[0x248];
    u8 *unk248;
} Arg0_003a31b0;

void CharaSysBattleResultReset_3a31b0(Arg0_003a31b0 *arg0) {
    u8 *temp_3;
    u8 *var_9;
    s32 var_8;
    u8 *var_7;
    s32 var_6;
    u8 *var_6_2;
    s32 var_5;

    temp_3 = arg0->unk248;
    if (temp_3 != NULL) {
        *(s32 *)(temp_3 + 0x0) = 0;
        var_8 = 0;
        var_9 = arg0->unk248 + 4;
        do {
            *(s16 *)(var_9 + 0x0) = -1;
            var_7 = var_9 + 0x10;
            *(s16 *)(var_9 + 0x2) = 0;
            var_6 = 0;
            *(s16 *)(var_9 + 0x4) = 0;
            *(s16 *)(var_9 + 0x6) = 0;
            *(s32 *)(var_9 + 0x8) = 0;
            *(s32 *)(var_9 + 0xC) = 0;
            do {
                *(s16 *)(var_7 + 0x0) = -1;
                var_6 += 1;
                *(s16 *)(var_7 + 0x2) = 0;
                var_7 += 4;
            } while (var_6 < 2);
            var_8 += 1;
            var_9 += 0x18;
        } while (var_8 < 0xA);
        var_5 = 0;
        *(s16 *)(arg0->unk248 + 0xF4) = 0;
        *(s16 *)(arg0->unk248 + 0xF6) = 0;
        var_6_2 = arg0->unk248 + 0xF8;
        do {
            *(s16 *)(var_6_2 + 0x0) = -1;
            var_5 += 1;
            *(s16 *)(var_6_2 + 0x2) = 0;
            var_6_2 += 4;
        } while (var_5 < 3);
    }
}
