#include "types.h"

typedef struct P {
    void *a;
    void *b;
} P;

extern void SoundIopSendCmdG2S0_165b20(s32 k, void *a, void *b);

void SoundThreadCmdSeqAttach_1b6b80(P *p)
{
    SoundIopSendCmdG2S0_165b20(0x5, p->a, p->b);
}
