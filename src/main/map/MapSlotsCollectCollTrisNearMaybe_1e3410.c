#include "types.h"

extern s32 MapAreaTreeCollectCollTrisNearMaybe_1dac30(s32, s32, s32, s32, f32, s32);

s32 MapSlotsCollectCollTrisNearMaybe_1e3410(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 f)
{
    s32 p;
    s32 n;
    s32 i;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    p = arg0 + 0x1928;
    n = 0;
    for (i = 0; i < 4; i++, p += 0x1CC) {
        n += MapAreaTreeCollectCollTrisNearMaybe_1dac30(p, arg1 + n * 0x60, arg2 - n, arg3, f, arg4);
        if (n >= arg2) {
            break;
        }
    }
    return n;
}
