#include "types.h"

typedef struct Obj001b6630 {
    s32 unk0;
    s32 unk4;
} Obj001b6630;

extern void sceSdRemote_1229e8(s32, s32, s32, s32);

s32 SoundThreadCmdSetReverbDepth_1b6630(Obj001b6630 *arg0)
{
    s32 temp16;
    s32 temp16_2;
    s32 temp17;

    temp17 = arg0->unk0 != 0;
    temp16 = arg0->unk4;
    sceSdRemote_1229e8(1, 0x8070, temp17 | 2, 1);
    temp16_2 = (temp16 << 8) & 0xFFFF;
    sceSdRemote_1229e8(1, 0x8010, temp17 | 0xB80, temp16_2);
    sceSdRemote_1229e8(1, 0x8010, temp17 | 0xC80, temp16_2);
    return 0;
}
