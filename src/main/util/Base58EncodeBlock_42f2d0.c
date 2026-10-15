#include "types.h"

extern s32 UDivDi3_139eb0(s32, s32);
extern s64 UModDi3_13a430(s32, s32);
extern s8 D_00455220[0x40];

void Base58EncodeBlock_42f2d0(u64 arg0, u8 *arg1) {
    s32 var_7;
    s32 var_16;

    for (var_7 = 0; var_7 < 11; var_7++) {
        arg1[var_7] = D_00455220[0];
    }
    var_16 = 0;
    while (arg0 != 0) {
        arg1[var_16] = D_00455220[(s32)(arg0 % 0x3A)];
        var_16 += 1;
        arg0 = arg0 / 0x3A;
    }
}
