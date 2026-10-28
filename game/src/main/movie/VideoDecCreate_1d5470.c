/* rgp:protos */
#define RGP_SELF_VideoDecCreate_1d5470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 MpegCreate_1104a8(u8 *, s32, s32);
s32 MpegAddCallback_1112c0(u8 *, s32, void *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 VideoDecCreate_1d5470(s32 pd0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    MpegCreate_1104a8(arg1, arg2, arg3);
    MpegAddCallback_1112c0(arg1, 0, VideoDecErrorCallback_1d4f40, 0);
    MpegAddCallback_1112c0(arg1, 1, VideoDecNodata_1d4f10, 0);
    MpegAddCallback_1112c0(arg1, 2, VideoDecStopDma_1d4ee0, 0);
    MpegAddCallback_1112c0(arg1, 3, VideoDecRestartDma_1d4eb0, 0);
    MpegAddCallback_1112c0(arg1, 5, VideoDecTimeStamp_1d4e60, 0);
    *(s32 *)(arg1 + 0xA8) = 0;
    ViBufCreate_1d46f0(arg1 + 0x48, arg4, arg5, arg6, arg7, arg8);
    return 1;
}
