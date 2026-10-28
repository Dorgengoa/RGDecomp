/* rgp:protos */
#define RGP_SELF_StreamChanClose_1d6dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x80]; s16 f80; } T_001d6dc0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StreamChanClose_1d6dc0(T_001d6dc0 *p)
{
    if (p->f80 >= 0) {
        StreamChanSetVolume_1d7010(p, 0.0f);
        StreamChanSetOpenReq_1d71a0(p, 0);
        StreamChanSetResumeReq_1d7170(p, 0);
        StreamChanSetPauseReq_1d7140(p, 1);
        StreamChanSetStopReq_1d7110(p, 1);
        StreamChanUpdate_1d72d0(p, 0.0f);
        SoundStreamSlotFree_1bd3a0(p->f80);
    }
    StreamChanInit_1d7610(p);
}
