#include "types.h"

extern s32 NumPutPadOutput_1a4610(s32, s32, s32, s32, void *, s32, void *, s32);
extern s32 NumPutFormatU64_1a4970(s32, s32, void *);

void NumPutU64_1a44f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 sp7F;
    u8 sp50[0x2F];

    NumPutPadOutput_1a4610(arg0, *(volatile s32 *)&arg1, arg2, arg3, &sp7F, 0, sp50, NumPutFormatU64_1a4970(arg2, arg4, sp50));
}
