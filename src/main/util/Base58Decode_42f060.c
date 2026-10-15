#include "types.h"

extern s32 Base58DecodeBlock_42f200(u8 *, void *);
extern s32 strlen(const char *);

s32 Base58Decode_42f060(u8 *arg0, u8 *arg1) {
    u8 sp68[8];
    s32 temp_2;
    s32 var_18;
    s32 var_17;
    s32 var_4;
    u8 *var_19;
    u8 *var_20;

    temp_2 = strlen((const char *)arg0);
    var_17 = 0;
    if ((temp_2 % 11) != 0) {
        return -1;
    }
    var_18 = 0;
    var_20 = arg0;
    var_19 = arg1;
    while (var_18 < temp_2) {
        if (Base58DecodeBlock_42f200(var_20, sp68) == 0) {
            return -1;
        }
        var_20 += 0xB;
        var_17 += 8;
        var_4 = 0;
        do {
            *var_19 = sp68[var_4];
            var_4 += 1;
            var_19 += 1;
        } while (var_4 < 8);
        var_18 += 0xB;
    }
    return var_17;
}
