/* rgp:protos */
#define RGP_SELF_EventCastSetMotionBlendSpeed_258250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Slot {
    s32 used;
    s32 pad4;
    s32 pad8;
    s32 obj;
} Slot;

/*rgp*/

#pragma opt_propagation off

s32 EventCastSetMotionBlendSpeed_258250(Slot *slots, s32 idx, float rgp_f0) {
    Slot *s;
    s32 obj, x, r;

    if (idx < 0 || idx >= 32) return 0;
    s = &slots[idx];
    if (s->used != 0) return 0;
    obj = s->obj;
    if (obj == 0) {
        r = 0;
    } else {
        ModelObjSetMotionBlendSpeed_1add60(obj, (float)rgp_f0);
        x = 1;
        goto out;
    }
    x = r;
out:
    return x;
}
