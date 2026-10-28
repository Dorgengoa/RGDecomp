/* rgp:protos */
#define RGP_SELF_LiveTalkCancel_3215c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void LiveTalkCancel_3215c0(u8 *arg0) {
    s32 h;
    s32 i;
    s32 k;
    s16 *p;
    s32 v;

    h = ((s32)GetStreamMgr_207ea0());
    if (h == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        p = (s16 *)(arg0 + i * 8);
        k = i + 1;
        v = StreamMgrChanGetStatus_1d65f0(h, k);
        if (*p == 2) {
            *p = 4;
            return;
        }
        if (*p == 3) {
            if (v == -1 || v == 1 || v == 3) {
                StreamMgrStopChan_1d66b0(h, k);
                *p = 4;
            } else if (v == 0) {
                StreamMgrStopChan_1d66b0(h, k);
                *p = 4;
            }
        }
    }
}
