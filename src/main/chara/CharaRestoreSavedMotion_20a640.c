#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern void MotionListResetAll_171e00(s32 arg0);
extern void ModelObjPlayMotionByName_1867a0(s32 arg0, void *arg1, s32 arg2);
extern void ModelObjUpdateMotions_1add20(s32, f32);
extern void ModelObjSetMotionPhase_1add80(s32 arg0, f32 arg1);
extern void ModelMotionEventReleaseHandlers_1b02b0(s32 arg0);
extern s32 ObjRecGetFlags_1c3d90(s32 arg0, s32 arg1, s16 arg2);
extern s32 GetCurrentScene_1f5be0(void);

void CharaRestoreSavedMotion_20a640(void *arg0) {
    s32 temp_3;

    if (*(s8 *)((u8 *)arg0 + 0xAE4) != 0) {
        temp_3 = *(s32 *)((u8 *)arg0 + 0x3F4);
        if (temp_3 != 0) {
            MotionListResetAll_171e00(temp_3 + 0x1F0);
            ModelObjPlayMotionByName_1867a0(*(s32 *)((u8 *)arg0 + 0x3F4), (u8 *)arg0 + 0xAE4,
                         *(s32 *)((u8 *)arg0 + 0xB08) | 4);
            ModelObjUpdateMotions_1add20(*(s32 *)((u8 *)arg0 + 0x3F4), 1.0f);
            ModelObjSetMotionPhase_1add80(*(s32 *)((u8 *)arg0 + 0x3F4), *(f32 *)((u8 *)arg0 + 0xB04));
            if (ObjRecGetFlags_1c3d90(GetCurrentScene_1f5be0(), 1, *(s16 *)((u8 *)arg0 + 0x424)) & 0x10) {
                ModelMotionEventReleaseHandlers_1b02b0(*(s32 *)((u8 *)arg0 + 0x3F4));
            }
        }
    }
    *(s8 *)((u8 *)arg0 + 0xAE4) = 0;
    *(s32 *)((u8 *)arg0 + 0xB04) = 0;
    *(s32 *)((u8 *)arg0 + 0xB08) = 4;
}
