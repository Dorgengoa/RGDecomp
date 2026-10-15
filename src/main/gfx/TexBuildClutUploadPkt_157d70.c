#include "types.h"

extern s32 GsBuildImageUploadRefPkt_158390(u8 *, s32, s32, s32, u32, s32, s32, s32, s64, s64);

s32 TexBuildClutUploadPkt_157d70(s32 arg0, u32 *arg1, u32 *arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 r;

    if (arg2 == NULL) {
        return 0;
    }
    r = 0;
    if (arg3 == 8) {
        arg1[0] = 0x20000000;
        arg1[1] = (u32)((u8 *)arg1 + 0x410) & 0x0FFFFFFF;
        arg1[2] = 0;
        arg1[3] = 0;
        *arg2 = (u32)((u8 *)arg1 + 0x10) & 0x0FFFFFFF;
        return GsBuildImageUploadRefPkt_158390((u8 *)arg1 + 0x410, arg4, arg5, 1, *arg2, 0x40, 0, 0, 0x10, 0x10) + 0x104;
    }
    if (arg3 == 4) {
        arg1[0] = 0x20000000;
        arg1[1] = (u32)((u8 *)arg1 + 0x50) & 0x0FFFFFFF;
        arg1[2] = 0;
        arg1[3] = 0;
        *arg2 = (u32)((u8 *)arg1 + 0x10) & 0x0FFFFFFF;
        r = GsBuildImageUploadRefPkt_158390((u8 *)arg1 + 0x50, arg4, arg5, 1, *arg2, 4, 0, 0, 8, 2) + 0x14;
    }
    return r;
}
