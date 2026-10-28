/* rgp:protos */
#define RGP_SELF_StreamChanGetRemainFrames_1d6a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 StreamChanGetRemainFrames_1d6a10(s32 arg0)
{
    s32 sp20[4] __attribute__((aligned(16)));
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
