#include "types.h"

extern s32 FindS16Index32_31be20(s32 xa0, s32 arg0);
extern void ScreenMarkerSetFlag_31bf70(s32 arg0, s32 arg1, s32 arg2);
extern s64 ScreenMarkerGetId_31c030(s32 arg0, s32 arg1);

void ScreenMarkerSetFlagById_31a900(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 temp_2;

    if (arg2 == -1) {
        for (i = 0; i < 0x20; i++) {
            if ((s16)ScreenMarkerGetId_31c030(arg0, i) != -1) {
                ScreenMarkerSetFlag_31bf70(arg0, i, arg1 & 0xFF);
            }
        }
        return;
    }
    temp_2 = FindS16Index32_31be20((s32)arg0, arg2);
    if (temp_2 != -1) {
        ScreenMarkerSetFlag_31bf70(arg0, temp_2, arg1 & 0xFF);
    }
}
