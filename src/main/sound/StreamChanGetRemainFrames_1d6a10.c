#include "types.h"

extern s32 StreamPlayAllowedMaybe_2f5210();
extern s32 StreamChanGetStatus_1d6bb0(s32);
extern void SoundStreamSlotGetBufInfo_1bd100(s32, s32);

s32 StreamChanGetRemainFrames_1d6a10(s32 arg0)
{
    s32 sp20[4];
    s32 num;
    s32 den;

    if ((StreamPlayAllowedMaybe_2f5210() != 0) && (*(s16 *)(arg0 + 0x80) >= 0)
        && (*(s16 *)(arg0 + 0xA0) > 0) && (StreamChanGetStatus_1d6bb0(arg0) == 1)) {
        SoundStreamSlotGetBufInfo_1bd100(*(s16 *)(arg0 + 0x80), (s32)&sp20[0]);
        num = *(s32 *)(arg0 + 0xA8) - sp20[1];
        den = *(s16 *)(arg0 + 0xA0);
        return (s32) ((30.0f * (f32) num) / (28672.0f * (f32) den));
    }
    return 0x708;
}
