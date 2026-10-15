#include "types.h"
#pragma opt_loop_invariants off

typedef struct Rng { s32 x0; s32 n; s32 on; } Rng;

void MotionListSelectByIndexAll_172030(void *arg0, s32 arg1, s32 arg2) {
    u8 *p;
    u8 *q;
    u8 *t;
    s32 ok;
    s32 lt;
    Rng *r;

    for (p = *(u8 **)((u8 *)arg0 + 4); p != NULL; p = *(u8 **)p) {
        q = p + 0x10;
        if (q == NULL) continue;
        t = *(u8 **)(q + 0x48);
        if (t == NULL) continue;
        r = (Rng *)(t + 0x10);
        if (*(s32 *)(t + 0x18) == 0) {
            ok = 0;
        } else if (arg1 >= 0) {
            lt = arg1 < r->n;
            if (lt == 0) {
                ok = 0;
            } else {
                ok = 1;
            }
        } else {
            ok = 0;
        }
        if (ok) {
            *(u8 **)q = t;
            *(s32 *)(q + 4) = arg1;
            *(s32 *)(q + 8) = arg2;
            *(s32 *)(q + 0x44) = 0;
        }
    }
}
