#include "types.h"

extern s32 FindS16Index32_31be20(void);
extern void ScreenMarkerSetFadeIn_31bf30(s32, s32, s32);
extern void ScreenMarkerSetFadeOut_31bf50(s32, s32, s32);
extern void ScreenMarkerSetFlag_31bf70(s32, s32, s32);
extern void ScreenMarkerSetTimer_31bf90(s32, s32, s32);
extern s32 ScreenMarkerGetFadeOut_31bff0(s32, s32);
extern s16 ScreenMarkerGetId_31c030(s32, s32);

void ScreenMarkerRestartById_31a9b0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 var_17;

    if (arg1 == -1) {
        var_17 = 0;
        do {
            if (ScreenMarkerGetId_31c030(arg0, var_17) != -1) {
                ScreenMarkerSetTimer_31bf90(arg0, var_17, 0x5A);
                ScreenMarkerSetFlag_31bf70(arg0, var_17, 1);
                ScreenMarkerSetFadeOut_31bf50(arg0, var_17, -1);
            }
            var_17 += 1;
        } while (var_17 < 0x20);
        return;
    }
    temp_2 = FindS16Index32_31be20();
    if (temp_2 != -1) {
        ScreenMarkerSetTimer_31bf90(arg0, temp_2, 0x5A);
        ScreenMarkerSetFlag_31bf70(arg0, temp_2, 1);
        ScreenMarkerSetFadeIn_31bf30(arg0, temp_2, (s32)(15.0f - (f32)ScreenMarkerGetFadeOut_31bff0(arg0, temp_2)));
        ScreenMarkerSetFadeOut_31bf50(arg0, temp_2, -1);
    }
}
