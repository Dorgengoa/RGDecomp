#include "types.h"
typedef struct { s32 a; s32 b; } E1efb10;
typedef struct { E1efb10 e[256]; s32 idx; } S1efb10;

s32 IdSlotTableAdd_1efb10(S1efb10 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 t;
    if ((arg1 == 0) || (arg2 < 0)) return -1;
    for (i = 0; i < 0x100; i++) {
        if (arg0->e[arg0->idx].a == 0) break;
        t = arg0->idx + 1;
        arg0->idx = t;
        if (t >= 0x100) arg0->idx = 0;
    }
    if (i >= 0x100) return -1;
    t = arg0->idx;
    arg0->e[t].a = arg1;
    arg0->e[t].b = arg2;
    arg0->idx = arg0->idx + 1;
    return t;
}
