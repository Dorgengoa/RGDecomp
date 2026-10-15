#include "types.h"

extern s32 FindS16Index32_31be20(void);

void ScreenMarkerAddOrUpdate_31be60(s32 arg0, s32 arg1, s8 arg2)
{
    s32 i;
    void *rec16;
    void *rec8;

    if (FindS16Index32_31be20() != -1) {
        *(s8 *)((u8 *)arg1 + arg0 + 0x120) = arg2;
        return;
    }
    for (i = 0; i < 0x20; i++) {
        rec16 = (u8 *)arg0 + i * 2;
        if (*(s16 *)rec16 == -1) {
            rec8 = (u8 *)arg0 + i;
            if (*(u8 *)((u8 *)rec8 + 0x80) == 0) {
                *(s16 *)rec16 = arg1;
                *(s16 *)((u8 *)rec16 + 0xE0) = 0xF;
                *(u8 *)((u8 *)rec8 + 0x80) = 1;
                *(s16 *)((u8 *)rec16 + 0xA0) = -1;
                *(s8 *)((u8 *)rec8 + 0x120) = arg2;
                return;
            }
        }
    }
}
