#include "types.h"
#pragma divbyzerocheck on

extern s32 FontIsAsciiCode_26ed80(s32, s32);
extern u8 FontGetCharWidth_26f4c0(s32, u16);
extern s16 FontGetGaijiWidth_26f890(s32, s32);

s32 TextCalcGapWidthMaybe_2741c0(s32 arg0, s32 arg1, s32 arg2, u16 *arg3)
{
    s32 c;
    s32 sum;
    s32 lines;

    sum = 0;
    lines = 0;
    for (;;) {
        c = *arg3++;
        switch (c) {
        case 0xFF00:
        case 0xFF03:
        case 0xFF01:
            if (lines > 0) {
                return (arg1 - sum) / lines;
            }
            return -1;
        case 0xFF02:
            lines++;
            break;
        default:
            if (c >= 0xFD00 && c < 0xFE00) {
                sum += FontGetGaijiWidth_26f890(arg0, c);
                break;
            }
            if (c >= 0xF900 && c < 0xFA00) {
                sum += c - 0xF900;
                break;
            }
            if (c >= 0xFC00 && c <= 0xFCFF) break;
            if (c >= 0xF500 && c <= 0xF5FF) break;
            if (c >= 0xF400 && c <= 0xF4FF) break;
            if (c >= 0xF300 && c <= 0xF3FF) break;
            if (c >= 0xF200 && c <= 0xF2FF) break;
            if (FontIsAsciiCode_26ed80(arg0, c) != 0) {
                sum += FontGetCharWidth_26f4c0(arg0, c);
            } else {
                sum += arg2;
            }
            break;
        }
    }
}
