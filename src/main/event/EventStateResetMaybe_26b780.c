#include "types.h"

typedef unsigned __int128 u128;

extern s32 D_004BD980[8];
extern s32 D_004BD9A0[8];
extern s32 D_004BD9A4[8];
extern s32 D_004BD9B0[8];
extern s32 D_004BD9B4[8];
extern s32 D_004BD9B8[8];
extern u128 D_004BD9C0;
extern u128 D_004BD9D0;
extern s32 D_004BD9E0[8];
extern s32 D_004BD9E4[8];
extern s32 D_004BDA20[8];
extern s32 D_004BDA24[8];

void EventStateResetMaybe_26b780(void)
{
    s32 *temp_3;
    s32 var_5;
    s32 var_6;
    u8 *temp_3_2;

    var_6 = 0;
    do {
        temp_3 = &D_004BD980[var_6];
        var_6 += 1;
        *temp_3 = -1;
    } while (var_6 < 8);
    D_004BD9E0[0] = 0;
    D_004BD9E4[0] = 0;
    D_004BDA20[0] = 0;
    D_004BDA24[0] = 0;
    D_004BD9B0[0] = 0;
    D_004BD9B4[0] = 0;
    D_004BD9C0 = 0;
    D_004BD9D0 = 0;
    D_004BD9B8[0] = -1;
    var_5 = 0;
    D_004BD9A0[0] = 0;
    do {
        temp_3_2 = (u8 *) &D_004BD980[var_5];
        var_5 += 1;
        *(s32 *) (temp_3_2 + 0xA8) = 0;
    } while (var_5 < 0xE0);
    D_004BD9A4[0] = 0;
}
