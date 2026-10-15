#include "types.h"
#pragma opt_common_subs off

s32 ArrayAddUnique_3f9c00(s32 arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *p;
    s32 i;

    p = arg1;
    if (arg0 == 0) {
        return arg3;
    }
    if (p == NULL) {
        return arg3;
    }
    if (arg2 <= arg3) {
        return arg3;
    }
    for (i = 0; i < arg3; i++, p++) {
        if (*p == arg0) {
            return arg3;
        }
    }
    *p = arg0;
    return arg3 + 1;
}
