#include "types.h"

extern s32 RecStackPopTo_1c4020(void *, s32);
extern s32 RecStackGetSlot_1c4330(void);

typedef struct { u8 pad[0x1704]; s32 arr[0x40]; s32 n; } T1c4;
s32 RecStackPop_1c4140(T1c4 *arg0, s32 arg1) {
    s32 var_16;
    s32 i;

    var_16 = -1;
    if (RecStackGetSlot_1c4330() == 0) {
        return var_16;
    }
    for (i = 0; i < arg0->n; i++) {
        if (arg0->arr[i] == arg1) {
            var_16 = i - 1;
            break;
        }
    }
    if (var_16 < 0) {
        return -1;
    }
    return RecStackPopTo_1c4020(arg0, arg0->arr[var_16]);
}
