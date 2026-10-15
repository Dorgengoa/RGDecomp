#include "types.h"

extern void PauseRequest_2f65e0(s32);
extern void DiscStatusMessageResetTimerRelated_39ece0(void);
extern void DiscStatusMessageDraw_39ecf0(s32);
extern s32 DiscWaitIsActive_39eeb0(void);
extern s16 D_004836E0;

s32 DiscStatusMessagePoll_39ee00(s32 arg0) {
    if ((D_004836E0 == 0) && (DiscWaitIsActive_39eeb0() != 0)) {
        D_004836E0 = 1;
        DiscStatusMessageResetTimerRelated_39ece0();
    }
    if (D_004836E0 == 1) {
        if (arg0 != 0) {
            DiscStatusMessageDraw_39ecf0(0);
        }
        if ((u8)((DiscWaitIsActive_39eeb0() != 0) ^ 1)) {
            D_004836E0 = 0;
        }
    }
    if (D_004836E0 == 0) {
        return 0;
    }
    PauseRequest_2f65e0(6);
    return 1;
    return 0;
}
