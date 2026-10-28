/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSetInputVolume_1b6570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void sceSdRemote_1229e8(s32, s32, s32, s32);

s32 SoundThreadCmdSetInputVolume_1b6570(void *p)
{
    s32 a = *(s32 *)((u8 *)p + 0);
    s32 flag = (a != 0);
    u32 tag = 0x8010;
    s32 b = *(s32 *)((u8 *)p + 4);

    sceSdRemote_1229e8(1, tag, flag | 0xF80, b);
    sceSdRemote_1229e8(1, tag, flag | 0x1080, b);
    return 0;
}
