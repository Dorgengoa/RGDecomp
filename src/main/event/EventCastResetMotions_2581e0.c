#include "types.h"

typedef struct Slot {
    s32 used;
    s32 pad4;
    s32 pad8;
    u8 *obj;
} Slot;

extern void MotionListResetAll_171e00(void *);

#pragma opt_propagation off

s32 EventCastResetMotions_2581e0(Slot *slots, s32 idx) {
    Slot *s;
    u8 *obj;
    s32 x, r;

    if (idx < 0 || idx >= 32) return 0;
    s = &slots[idx];
    if (s->used != 0) return 0;
    obj = s->obj;
    if (obj == 0) {
        r = 0;
    } else {
        MotionListResetAll_171e00(obj + 0x1F0);
        x = 1;
        goto out;
    }
    x = r;
out:
    return x;
}
