/* rgp:protos */
#define RGP_SELF_SoundThreadCmdNoteStreamAttachMaybe_1b6b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P {
    void *a;
    void *b;
} P;

/*rgp*/

void SoundThreadCmdNoteStreamAttachMaybe_1b6b60(P *p)
{
    SoundIopSendCmdG3S0_165dc8(0x5, p->a, p->b);
}
