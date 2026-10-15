#include "types.h"

struct Slot {
    s32 a;
    s32 b;
};

extern f32 ScriptSlotGetFloat_334890(struct Slot *a);
extern f32 Atan2f_1291a8(f32 y, f32 x);
extern void ScriptSlotStoreFloatRef_3347d0(struct Slot *a, f32 v);

s32 ScriptCmdAtan2_3342e0(void *a0, s32 mode)
{
    struct Slot *p;
    f32 x;
    f32 y;

    p = (struct Slot *)a0;
    if (mode != 3) {
        return 0;
    }
    x = ScriptSlotGetFloat_334890(p++);
    y = ScriptSlotGetFloat_334890(p++);
    ScriptSlotStoreFloatRef_3347d0(p, Atan2f_1291a8(x, y));
    return 1;
}
