#include "types.h"

extern void MemStackReset_14d830(s32 arg0);
extern void HandleEntryFreeRes_3f1420(void);
extern s32 MemStackArrayGet_3f15a0(s32 arg0, s16 arg1);
extern void HandleEntryInit_3f40a0(void *arg0);

s32 HandleEntryRelease_3f12f0(s32 arg0, void *arg1, s32 arg2)
{
    s32 temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    if (arg2 != 0) {
        HandleEntryFreeRes_3f1420();
    }
    temp_2 = MemStackArrayGet_3f15a0(arg0, *(s16 *)((u8 *)arg1 + 0xC));
    if (temp_2 != 0) {
        MemStackReset_14d830(temp_2);
    }
    if (arg2 != 0) {
        HandleEntryInit_3f40a0(arg1);
    }
    return 1;
}
