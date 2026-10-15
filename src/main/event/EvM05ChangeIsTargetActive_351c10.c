#include "types.h"

extern s32 TargetRefIsValid_2e6e40(void *);
extern s32 EvTargetIsBound_3526a0(s32);

s32 EvM05ChangeIsTargetActive_351c10(u8 *arg0) {
    s32 p;
    s32 i;

    if (arg0 + 0xE0 == NULL) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x13C) == 0) {
        return 0;
    }
    if (TargetRefIsValid_2e6e40(arg0 + 0xA0) == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0xE8);
    for (i = 0; i < *(s32 *)(arg0 + 0xEC); i++, p += 0x140) {
        if (EvTargetIsBound_3526a0(p) == 0) {
            return 0;
        }
    }
    return 1;
}
