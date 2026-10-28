/* rgp:protos */
#define RGP_SELF_SoundSendVolume_1b8020 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- the varargs call passes (..., 0, arg3, vol): the draft had the
   last two swapped; and arg4 is clamped IN PLACE (a var_10 copy swaps t2/t3). */
#include "types.h"

/*rgp*/
extern s32 D_004A1E40[];

#pragma divbyzerocheck on
void SoundSendVolume_1b8020(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg4 < 0) {
        arg4 = 0x7F;
    }
    if ((arg0 >= 0) && ((u32)arg0 < 0x10U)) {
        arg4 = (s32)(arg4 * D_004A1E40[arg0]) / 127;
    }
    SoundSendCmd_1b6cc0(0x1D, 5, arg0, arg5, 0, arg3, arg4);
}
