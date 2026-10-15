#include "types.h"
#pragma opt_common_subs off

extern s32 SoundIopSendCmdG3S2_165f20(s32, s32, ...);

s32 SoundThreadCmdKeyOn_1b6800(void *arg0) {
    s32 result;

    result = SoundIopSendCmdG3S2_165f20(*(s32 *)((u8 *)arg0 + 0x0), 0x11, *(s32 *)((u8 *)arg0 + 0x4),
                           *(s32 *)((u8 *)arg0 + 0x8), *(s32 *)((u8 *)arg0 + 0xC),
                           *(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 0x14),
                           *(s32 *)((u8 *)arg0 + 0x18), (s64) * (s32 *)((u8 *)arg0 + 0x1C));
    SoundIopSendCmdG3S2_165f20(*(s32 *)((u8 *)arg0 + 0x0), 0x42, *(s32 *)((u8 *)arg0 + 0x4),
                 *(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 0x14),
                 *(s32 *)((u8 *)arg0 + 0x20));
    SoundIopSendCmdG3S2_165f20(*(s32 *)((u8 *)arg0 + 0x0), 0x41, *(s32 *)((u8 *)arg0 + 0x4),
                 *(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 0x14),
                 *(s32 *)((u8 *)arg0 + 0x24));
    return result;
}
