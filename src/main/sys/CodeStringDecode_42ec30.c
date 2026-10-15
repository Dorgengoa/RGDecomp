#include "types.h"
#pragma optimize_for_size on
#pragma divbyzerocheck on

extern s32 CodeCipherDecode_42edb0(s32, s32, s32, s32);
extern s32 Base58Decode_42f060(s32, s32);
extern s32 strlen(s32);

s32 CodeStringDecode_42ec30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_2;
    s32 len;
    s32 r;

    len = strlen(arg0);
    if (len % 11 != 0) {
        return 0;
    }
    if (arg2 < (len / 11) * 8) {
        return 0;
    }
    temp_2 = Base58Decode_42f060(arg0, arg1);
    if (temp_2 <= 0) {
        return 0;
    }
    return CodeCipherDecode_42edb0(arg1, temp_2, arg3, arg4) != 0;
}
