#include "types.h"

typedef struct {
    u8 pad[0x2AC];
    u8 unk2AC;
    u8 pad2[0x2C0 - 0x2AD];
    f32 unk2C0;
    f32 unk2C4;
    s32 unk2C8;
    s32 unk2CC;
    f32 unk2D0;
    f32 unk2D4;
    f32 unk2D8;
    s32 unk2DC;
} S003058c0_arg0;

extern void VecNormalize_1cbb80(void *, void *);
extern f32 sqrtf(f32);

void CameraShakeStart_3058c0(S003058c0_arg0 *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    void *temp_4;

    arg0->unk2AC = 0;
    arg0->unk2C0 = fparg0;
    arg0->unk2C4 = fparg1;
    arg0->unk2C8 = 0;
    arg0->unk2CC = 0x3F800000;
    temp_4 = (u8 *)arg0 + 0x2C0;
    VecNormalize_1cbb80(temp_4, temp_4);
    arg0->unk2D0 = sqrtf(fparg0 * fparg0 + fparg1 * fparg1);
    arg0->unk2D4 = fparg2;
    arg0->unk2D8 = fparg3;
    arg0->unk2DC = 0;
}
