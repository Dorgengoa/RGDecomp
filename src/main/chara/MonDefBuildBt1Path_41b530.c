#include "types.h"

extern void strcat(s32, void *);
extern void strcpy(s32, s32);
extern u8 D_00467E08[];

s32 MonDefBuildBt1Path_41b530(void *arg0, s32 arg1, void *arg2)
{
    s32 temp_5;

    if (arg1 == 0) {
        return 0;
    }
    if (!(*(u8*)((u8 *)arg0 + 0xC) & 1)) {
        return 0;
    }
    if (*(s32*)((u8 *)arg0 + 0x0) == 0) {
        return 0;
    }
    strcpy(arg1, *(s32*)((u8 *)arg0 + 0x0));
    strcat(arg1, D_00467E08);
    if (arg2 != NULL) {
        strcat(arg1, arg2);
    }
    return 1;
}
