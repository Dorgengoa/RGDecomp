#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off
typedef char *va_list;

extern s32 SoundQueueCmd_1b6d60(s32, s32 *, s32);

s32 SoundSendCmd_1b6cc0(s32 arg0, s32 count, ...) {
    s32 args[10];
    va_list ap;
    s32 i;
    s32 n;
    s32 k;

    if (count > 0xa) {
        return -1;
    }
    n = 2;
    ap = (va_list)__builtin_next_arg(count) - (n >= 8 ? 0 : (8 - n) * 8);
    for (i = 0; i < count; i++) {
        ap += 8;
        args[i] = *(s32 *)(ap - 8);
    }
    return SoundQueueCmd_1b6d60(arg0, args, 0x28);
}
