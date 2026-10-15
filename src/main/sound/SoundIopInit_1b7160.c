#include "types.h"

extern s32 SoundInitStub_165600(s32 arg0);
extern s32 SdRemoteInitMasterVolume_165608(s32 arg0);
extern void SoundIopSendCmdG0S2_1656b8(s32 a, ...);

extern s32 D_0047E1F0;
extern u8 D_0049D540[];

void SoundIopInit_1b7160(void)
{
    s32 i;

    SoundInitStub_165600(0);
    D_0047E1F0 = SdRemoteInitMasterVolume_165608(5);
    SoundIopSendCmdG0S2_1656b8(0, 0x8F, 0x880);
    SoundIopSendCmdG0S2_1656b8(3, 0x83, 0x105, 0, 0);
    SoundIopSendCmdG0S2_1656b8(3, 0x82, 0);
    SoundIopSendCmdG0S2_1656b8(3, 0x80, 0x7F, 0x7F);

    for (i = 0; i < 0x27; i++) {
        D_0049D540[i] = 0;
    }
}
