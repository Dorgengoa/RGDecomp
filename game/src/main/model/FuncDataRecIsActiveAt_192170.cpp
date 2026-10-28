#include "types.h"
inline s32 inRange(f32 x, f32 lo, f32 hi)
{
    if (!(hi <= lo)) {
        if (x < lo) {
            return 0;
        }
        if (!(x < hi)) {
            return 0;
        }
        return 1;
    }
    if (!(lo <= hi)) {
        if (!(x < lo)) {
            return 1;
        }
        if (x < hi) {
            return 1;
        }
        return 0;
    }
    return 1;
}
extern "C" s32 FuncDataRecIsActiveAt_192170(void *arg0, f32 *arg1)
{
    if (*(s32 *)((u8 *)arg0 + 0x44) == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 1;
    }
    return inRange(*arg1, *(f32 *)((u8 *)arg0 + 0x58), *(f32 *)((u8 *)arg0 + 0x5C));
}
