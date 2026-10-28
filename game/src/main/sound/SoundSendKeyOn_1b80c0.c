/* rgp:protos */
#define RGP_SELF_SoundSendKeyOn_1b80c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
/*rgp*/
extern s32 D_004814D0;
extern u8 D_004A1E40[0x400];

void SoundSendKeyOn_1b80c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s64 arg4, s32 arg5, s64 arg6, s64 arg7, s32 arg_sp0)
{
    s32 t;

    if (arg5 < 0) {
        arg5 = 0x7F;
    }
    if (arg4 < 0) {
        arg4 = 0x7F;
    }
    if ((arg0 >= 0) && ((u32) arg0 < 0x10U)) {
        arg5 = (arg5 * ((s32 *)D_004A1E40)[arg0]) / 127;
    }
    if ((arg_sp0 == -1) || (arg_sp0 < 0)) {
        t = (D_004814D0 + 1) % 25;
        D_004814D0 = t;
        arg_sp0 = t + 0x66;
    }
    SoundSendCmd_1b6cc0(0x20, 0xA, arg0, arg_sp0, arg1, arg2, 0, arg3, (s32)(arg4), (s32)(arg6), arg5, (s32)(arg7));
}
