#include "types.h"
#pragma opt_common_subs off

extern f32 ModelObjGetMotionPhase_1add70(s32 arg0);
extern s32 CharaGetMotionPlayFlags_238550(void *arg0);
extern s32 strcmp(const char *a, const char *b);
extern void strcpy(void *dst, const void *src);

void CharaSaveMotion_20a6f0(void *arg0) {
    void *temp_16;

    if (*(s32*)((u8 *)arg0 + 0x3F4) != 0) {
        temp_16 = (u8 *)arg0 + 0xA8C;
        if (temp_16 != NULL) {
            strcpy((u8 *)arg0 + 0xAE4, temp_16);
            *(s32*)((u8 *)arg0 + 0xB08) = CharaGetMotionPlayFlags_238550(arg0);
            if (strcmp((const char *)((u8 *)arg0 + 0xAE4), (const char *)temp_16) == 0) {
                *(f32 *)((u8 *)arg0 + 0xB04) = ModelObjGetMotionPhase_1add70(*(s32*)((u8 *)arg0 + 0x3F4));
            } else {
                *(f32 *)((u8 *)arg0 + 0xB04) = 0.0f;
            }
        }
    } else {
        *(s8*)((u8 *)arg0 + 0xAE4) = 0;
        *(f32 *)((u8 *)arg0 + 0xB04) = 0.0f;
        *(s32*)((u8 *)arg0 + 0xB08) = 4;
    }
}
