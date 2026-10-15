#include "types.h"

extern void McBuildSaveDirPath_376460(s32, s32);
extern void *strcat(void *, void *);

extern u8 D_00463A18[];
extern u8 D_00463A28[];

void McBuildIconPath_376400(s32 arg0, s32 arg1, s32 arg2)
{
    McBuildSaveDirPath_376460(arg0, arg1);
    if (arg2 == 0) {
        strcat((void *)arg0, D_00463A18);
    } else {
        strcat((void *)arg0, D_00463A28);
    }
}
