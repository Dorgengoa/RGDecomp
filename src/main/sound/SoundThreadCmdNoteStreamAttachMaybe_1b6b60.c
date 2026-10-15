#include "types.h"

typedef struct P {
    void *a;
    void *b;
} P;

extern void SoundIopSendCmdG3S0_165dc8(s32 k, void *a, void *b);

void SoundThreadCmdNoteStreamAttachMaybe_1b6b60(P *p)
{
    SoundIopSendCmdG3S0_165dc8(0x5, p->a, p->b);
}
