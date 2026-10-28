/* rgp:protos */
#define RGP_SELF_AudioDecPause_1d3140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 AudioDecPause_1d3140(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0) = 3;
    AudioDecSetInputVolume_1d2b90(0);
    *(s32 *)((u8 *)arg0 + 0x50) = (SoundSendCmd_1b6cc0(0x26, 6, 0x80E0, 0, 2, 0, 0, 0) & 0xffffff) - *(s32 *)((u8 *)arg0 + 0x44);
    SoundSendCmd_1b6cc0(0x26, 6, 0x80D0, 0, 8, *(s32 *)((u8 *)arg0 + 0x58), 0x4000, 0x800);
    return 0;
}
