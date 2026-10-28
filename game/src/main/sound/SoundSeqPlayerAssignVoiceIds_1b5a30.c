/* rgp:protos */
#define RGP_SELF_SoundSeqPlayerAssignVoiceIds_1b5a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SoundSeqPlayerAssignVoiceIds_1b5a30(u8 *p)
{
    s32 i;

    for (i = 0; i < *(s32 *)(p + 0x2C); i++) {
        *(s8 *)(p + i * 12 + 0x36) = SoundNextVoiceId_1b81a0();
    }
}
