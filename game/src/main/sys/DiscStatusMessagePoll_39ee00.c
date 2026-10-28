/* rgp:protos */
#define RGP_SELF_DiscStatusMessagePoll_39ee00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_004836E0;

s32 DiscStatusMessagePoll_39ee00(s32 arg0) {
    if ((D_004836E0 == 0) && (((unsigned char)DiscWaitIsActive_39eeb0()) != 0)) {
        D_004836E0 = 1;
        DiscStatusMessageResetTimerRelated_39ece0();
    }
    if (D_004836E0 == 1) {
        if (arg0 != 0) {
            DiscStatusMessageDraw_39ecf0(0);
        }
        if ((u8)((((unsigned char)DiscWaitIsActive_39eeb0()) != 0) ^ 1)) {
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
