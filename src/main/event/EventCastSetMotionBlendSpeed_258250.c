#include "types.h"

typedef struct Slot {
    s32 used;
    s32 pad4;
    s32 pad8;
    s32 obj;
} Slot;

extern s32 ModelObjSetMotionBlendSpeed_1add60(s32);

#pragma opt_propagation off

s32 EventCastSetMotionBlendSpeed_258250(Slot *slots, s32 idx) {
    Slot *s;
    s32 obj, x, r;

    if (idx < 0 || idx >= 32) return 0;
    s = &slots[idx];
    if (s->used != 0) return 0;
    obj = s->obj;
    if (obj == 0) {
        r = 0;
    } else {
        ModelObjSetMotionBlendSpeed_1add60(obj);
        x = 1;
        goto out;
    }
    x = r;
out:
    return x;
}
