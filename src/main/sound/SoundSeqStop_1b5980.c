#pragma opt_propagation off
#include "types.h"

extern void SoundSendKeyOff_1b8090(s32, s32, s8, s8, s8);

void SoundSeqStop_1b5980(void *arg0)
{
    s32 i;
    s32 ok;
    s32 c;
    s8 *e;

    for (i = 0; i < *(s32 *)((u8 *)arg0 + 0x2C); i++) {
        if (i >= 0) {
            c = i < *(s32 *)((u8 *)arg0 + 0x2C);
            if (!c) {
                ok = 0;
            } else {
                ok = 1;
            }
        } else {
            ok = 0;
        }
        if (ok != 0) {
            e = (s8 *)arg0 + i * 0xC + 0x38;
            SoundSendKeyOff_1b8090(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), e[1], e[2], e[3]);
            e[0] = 0;
        }
    }
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
}
