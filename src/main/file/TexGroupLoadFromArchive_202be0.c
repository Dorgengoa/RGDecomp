#include "types.h"

extern s32 ArchiveGetFileByPath_1c2800(s32 arg0, s32 arg1, volatile s32 *arg2);
extern s32 TexGroupLoadFromBuf_202ad0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

s32 TexGroupLoadFromArchive_202be0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile s32 sp4C;
    s32 temp_2;

    if (((arg0 == 0) || (arg1 == 0)) || (arg2 == 0)) return -1;
    sp4C = 0;
    temp_2 = ArchiveGetFileByPath_1c2800(arg0, arg1, &sp4C);
    if (temp_2 == 0 || sp4C <= 0) {
        return -1;
    }
    return TexGroupLoadFromBuf_202ad0(temp_2, sp4C, arg2, arg3, arg4, 0, 0);
}
