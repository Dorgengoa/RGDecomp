/* rgp:protos */
#define RGP_SELF_StreamChan1SetVolumeFade_2072f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void StreamChan1SetVolumeFade_2072f0(void *p, f32 v)
{
    void *q;

    q = GetStreamMgr_207ea0();
    StreamMgrSetChanVolumeFade_1d63a0(q, 1, p, v);
}
