#include "types.h"

typedef struct Q_001bd3a0 {
    u8 b[296];
} Q_001bd3a0;

extern Q_001bd3a0 D_004A25F0[];
extern s32 D_004814F0[2];
extern void SoundStreamSlotShutdown_1bdfd0(Q_001bd3a0 *);

s32 SoundStreamSlotFree_1bd3a0(s32 i)
{
    Q_001bd3a0 *q;

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
    if (q == 0) {
        return -1;
    }
    SoundStreamSlotShutdown_1bdfd0(q);
    D_004814F0[i] = 0;
    return i;
}
