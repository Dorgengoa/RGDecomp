#pragma opt_propagation off
#include "types.h"

extern s32 SaveCalcSizeKB_3735e0(void *);
extern void SaveProgressReset_373670(void);

void SaveSetProgressTotal_375a50(void *arg0, s32 arg1)
{
    s32 temp_4;
    s32 v;

    SaveProgressReset_373670();
    temp_4 = arg1 & 0xFF;
    if (temp_4 == 0) {
        v = SaveCalcSizeKB_3735e0(arg0) << 0xA;
        *(s32 *)((u8 *)arg0 + 0x520) = v;
        v += 0x3C4;
        *(s32 *)((u8 *)arg0 + 0x520) = v;
        *(s32 *)((u8 *)arg0 + 0x520) = v + 0x16800;
    } else if (temp_4 == 1) {
        v = *(s32 *)((u8 *)arg0 + 0x510);
        *(s32 *)((u8 *)arg0 + 0x520) = v;
        v += 0x3C4;
        *(s32 *)((u8 *)arg0 + 0x520) = v;
        *(s32 *)((u8 *)arg0 + 0x520) = v + 0xDC00;
    } else if (temp_4 == 2) {
        *(s32 *)((u8 *)arg0 + 0x520) = *(s32 *)((u8 *)arg0 + 0x510);
    } else if (temp_4 == 3) {
        *(s32 *)((u8 *)arg0 + 0x520) = 0x140;
    } else {
        *(s32 *)((u8 *)arg0 + 0x520) = *(s32 *)((u8 *)arg0 + 0x510);
    }
    *(s32 *)((u8 *)arg0 + 0x524) = 0;
}
