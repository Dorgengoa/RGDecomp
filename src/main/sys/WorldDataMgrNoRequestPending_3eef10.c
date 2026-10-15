#include "types.h"

extern const s32 D_004644A0;
extern const s32 D_004644C8;

s32 WorldDataMgrNoRequestPending_3eef10(void *arg0) {
    s32 var_2;
    u8 *var_7;
    s32 var_6;
    u8 *var_8;
    s32 var_7_2;
    u8 *var_8_2;
    s32 var_7_3;

    var_2 = 0;
    var_6 = 0;
    var_7 = *(u8 **)((u8 *)arg0 + 0xC);
    do {
        if (*(s16 *)(var_7 + 0x4) == 2) {
            var_2 += 1;
        }
        var_6 += 1;
        var_7 += 0x1C;
    } while (var_6 < 2);

    var_8 = *(u8 **)((u8 *)arg0 + 0x18);
    var_7_2 = 0;
    while (var_7_2 < D_004644A0) {
        if (*(s16 *)(var_8 + 0xC) == 2) {
            var_2 += 1;
        }
        var_7_2 += 1;
        var_8 += 0x28;
    }

    var_8_2 = *(u8 **)((u8 *)arg0 + 0x20);
    var_7_3 = 0;
    while (var_7_3 < D_004644C8) {
        if (*(s16 *)(var_8_2 + 0x8) == 2) {
            var_2 += 1;
        }
        var_7_3 += 1;
        var_8_2 += 0x20;
    }

    if (*(s16 *)(*(u8 **)((u8 *)arg0 + 0x28) + 0x2) == 2) {
        var_2 += 1;
    }
    return var_2 == 0;
}
