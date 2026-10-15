#include "types.h"

/* PARK (3 rounds): 0x148 vs retail 0x14C -- 4 bytes (1 word) short, very
   close. m2c: "jr instruction ... jump table not provided" (real
   jtbl_00462C30, not captured by the single-symbol listing). Reconstructed
   by hand: the switch over digit is a dense 0-9 jump table whose case
   bodies are visible right
   after the jr in the .s. */

#pragma divbyzerocheck on

extern u8 D_004E8F40[0x400];

void MenuFormat3Digits_35cb40(void *arg0, s32 arg1, s32 arg2)
{
    s32 digits[3];
    s32 i;
    s32 digit;
    s32 rem100;

    digits[0] = arg1 / 100;
    rem100 = arg1 % 100;
    digits[1] = rem100 / 10;
    digits[2] = rem100 % 10;
    for (i = 0; i < 3; i++) {
        digit = digits[i];
        switch (digit) {
        case 0: D_004E8F40[arg2 * 4 + i] = '0'; break;
        case 1: D_004E8F40[arg2 * 4 + i] = '1'; break;
        case 2: D_004E8F40[arg2 * 4 + i] = '2'; break;
        case 3: D_004E8F40[arg2 * 4 + i] = '3'; break;
        case 4: D_004E8F40[arg2 * 4 + i] = '4'; break;
        case 5: D_004E8F40[arg2 * 4 + i] = '5'; break;
        case 6: D_004E8F40[arg2 * 4 + i] = '6'; break;
        case 7: D_004E8F40[arg2 * 4 + i] = '7'; break;
        case 8: D_004E8F40[arg2 * 4 + i] = '8'; break;
        case 9: D_004E8F40[arg2 * 4 + i] = '9'; break;
        }
    }
}
