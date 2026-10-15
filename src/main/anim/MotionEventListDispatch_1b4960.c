#include "types.h"

extern s32 MotionEventBlockDispatch_1b2490(void *, s32, s32, f32, f32);

s32 MotionEventListDispatch_1b4960(void **arg0, s32 arg1, s32 arg2, s32 arg3, f32 f0, f32 f1)
{
    void *node;
    s32 total;
    u8 *sub;

    total = 0;
    node = *arg0;
    while (node != NULL) {
        sub = (u8 *)node + 0x10;
        if (arg1 == *(s32 *)sub) {
            total += MotionEventBlockDispatch_1b2490(sub, arg3, arg2 != *(s32 *)(sub + 4), f0, f1);
        }
        node = *(void **)node;
    }
    return total;
}
