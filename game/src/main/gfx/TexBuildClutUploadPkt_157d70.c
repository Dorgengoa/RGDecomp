/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_TexBuildClutUploadPkt_157d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 TexBuildClutUploadPkt_157d70(s32 arg0, u32 *arg1, u32 *arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 r;

    if (arg2 == NULL) {
        return 0;
    }
    r = 0;
    if (arg3 == 8) {
        arg1[0] = 0x20000000;
        arg1[1] = ((u32)((u8 *)arg1 + 0x410));
        arg1[2] = 0;
        arg1[3] = 0;
        *arg2 = ((u32)((u8 *)arg1 + 0x10));
        return GsBuildImageUploadRefPkt_158390((u8 *)arg1 + 0x410, arg4, arg5, 1, *arg2, 0x40, 0, 0, (int)(0x10), (int)(0x10)) + 0x104;
    }
    if (arg3 == 4) {
        arg1[0] = 0x20000000;
        arg1[1] = ((u32)((u8 *)arg1 + 0x50));
        arg1[2] = 0;
        arg1[3] = 0;
        *arg2 = ((u32)((u8 *)arg1 + 0x10));
        r = GsBuildImageUploadRefPkt_158390((u8 *)arg1 + 0x50, arg4, arg5, 1, *arg2, 4, 0, 0, (int)(8), (int)(2)) + 0x14;
    }
    return r;
}
