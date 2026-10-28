/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSeqAttach_1b6b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P {
    void *a;
    void *b;
} P;

/*rgp*/

void SoundThreadCmdSeqAttach_1b6b80(P *p)
{
    SoundIopSendCmdG2S0_165b20(0x5, p->a, p->b);
}
