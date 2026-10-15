#include "types.h"

struct Slot {
    s32 a;
    s32 b;
};

extern f32 ScriptSlotGetFloat_2cc9a0(struct Slot *a);
extern f32 Atan2f_1291a8(f32 y, f32 x);
extern void ScriptSlotStoreFloatRef_2cc8e0(struct Slot *a, f32 v);

s32 AiCmdAtan2_2cc1e0(void *a0, s32 mode)
{
    struct Slot *p;
    f32 x;
    f32 y;

    p = (struct Slot *)a0;
    if (mode != 3) {
        return 0;
    }
    x = ScriptSlotGetFloat_2cc9a0(p++);
    y = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreFloatRef_2cc8e0(p, Atan2f_1291a8(x, y));
    return 1;
}
