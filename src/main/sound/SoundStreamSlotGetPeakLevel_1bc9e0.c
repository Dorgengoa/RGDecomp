#include "types.h"

typedef struct Q_001bc9e0 {
    u8 pad0[0xEC];
    s32 fEC;
    u8 padF0[56];
} Q_001bc9e0;

extern Q_001bc9e0 D_004A25F0[];
extern s32 D_004814F0[2];

s32 SoundStreamSlotGetPeakLevel_1bc9e0(s32 i)
{
    Q_001bc9e0 *q;

    if (i < 0 || i >= 4) {
        q = 0;
    } else {
        q = &D_004A25F0[i];
    }
    if (q != 0) {
        if (D_004814F0[i] == 0) {
            q = 0;
        }
    } else {
        q = 0;
    }
    if (q == 0) return 0;
    return q->fEC;
}
