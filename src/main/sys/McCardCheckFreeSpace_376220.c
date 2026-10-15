#include "types.h"

s32 McCardCheckFreeSpace_376220(void *arg0, s32 arg1) {
    if (arg0 == 0) {
        return 3;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x0) == 0) || (!(*(s32 *)((u8 *)arg0 + 0x4) == 2))) return 1;
    if (*(s32 *)((u8 *)arg0 + 0x8) != 0) {
        if (*(s32 *)((u8 *)arg0 + 0x10) < arg1) {
            return 2;
        }
    }
    return 0;
    return 1;
}
