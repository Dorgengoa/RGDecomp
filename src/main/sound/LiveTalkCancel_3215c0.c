#include "types.h"

extern s32 StreamMgrChanGetStatus_1d65f0(s32, s32);
extern void StreamMgrStopChan_1d66b0(s32, s32);
extern s32 GetStreamMgr_207ea0(void);

void LiveTalkCancel_3215c0(u8 *arg0) {
    s32 h;
    s32 i;
    s32 k;
    s16 *p;
    s32 v;

    h = GetStreamMgr_207ea0();
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
