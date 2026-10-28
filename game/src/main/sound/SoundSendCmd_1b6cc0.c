/* rgp:protos */
#define RGP_SELF_SoundSendCmd_1b6cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off
#include <stdarg.h>


/*rgp*/

s32 SoundSendCmd_1b6cc0(s32 arg0, s32 count, ...) {
    s32 args[10] __attribute__((aligned(16)));
    va_list ap __attribute__((aligned(16)));
    s32 i;
    s32 n;
    s32 k;

    if (count > 0xa) {
        return -1;
    }
    n = 2;
    va_start(ap, count);
    for (i = 0; i < count; i++) {
        
        args[i] = va_arg(ap, s32);
    }
    return SoundQueueCmd_1b6d60(arg0, args, 0x28);
}
