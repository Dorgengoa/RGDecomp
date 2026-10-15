#include "types.h"

extern s32 PadIsHeld_183a20(void *, s32);
extern f32 PadGetAnalogRYNorm_183b90(void *);
extern void PadGetAnalogRXNorm_183c30(void *);
extern void CameraFollowLeaderStepMaybe_3081e0(void *, s32, s32, s32, s32, s32);
extern u8 D_004B2570[];

void CameraModeZoomUpdate_306200(void *arg0, s32 arg1) {
    f32 temp_f0;
    f32 *fieldPtr;

    fieldPtr = (f32 *)((u8 *)arg0 + 0x15C);
    if (PadIsHeld_183a20(D_004B2570, 2) != 0) {
        PadGetAnalogRXNorm_183c30(D_004B2570);
        temp_f0 = *fieldPtr +
                  (-10.0f) * ((f32)*(s32 *)((u8 *)arg0 + 0x254) * PadGetAnalogRYNorm_183b90(D_004B2570));
        *fieldPtr = temp_f0;
        if (temp_f0 < 30.0f) {
            *fieldPtr = 30.0f;
        }
        fieldPtr[1] = 10.0f + *fieldPtr;
    }
    CameraFollowLeaderStepMaybe_3081e0(arg0, arg1, 0, 0, 0, 0);
}
