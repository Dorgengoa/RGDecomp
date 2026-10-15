#include "types.h"

extern void ModelApplyMotionBlend_171680(void *, s32, s32, f32, f32, f32);
extern void ModelApplyMotion_171a10(void *, s32, f32);
extern void MotionPlayerGetBlendMaybe_172ce0(void *, void *);

void ModelObjApplyMotionList_186700(void *arg0) {
    void *node;
    void *temp4;
    u8 buf[0x18];

    node = *(void **)((u8 *)arg0 + 0x1F4);
    if (node == 0) {
        return;
    }
    while (node != 0) {
        temp4 = (u8 *)node + 0x10;
        if (temp4 != 0) {
            MotionPlayerGetBlendMaybe_172ce0(temp4, buf);
            if (!(*(s32 *)(buf + 0x0) != 0)) {
                ModelApplyMotion_171a10(arg0, *(s32 *)(buf + 0x8), *(f32 *)(buf + 0xC));
            } else {
                ModelApplyMotionBlend_171680(arg0, *(s32 *)(buf + 0x8), *(s32 *)(buf + 0x10),
                             *(f32 *)(buf + 0xC), *(f32 *)(buf + 0x14), *(f32 *)(buf + 0x4));
            }
        }
        node = *(void **)node;
    }
}
