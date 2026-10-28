/* rgp:protos */
#define RGP_SELF_EvSubNodePlayMotion_252630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
/*rgp*/
/*rgp*/
extern u8 D_004BDDB0[0x400];

s32 EvSubNodePlayMotion_252630(void *arg0, void *arg1) {
    s32 *temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x28) == 0) {
        if (EventCastMotionIsFinished_258340(D_004BDDB0, *(s32 *)((u8 *)arg1 + 0x60)) != 0) {
            EventCastPlayMotion_2583a0(D_004BDDB0, *(s32 *)((u8 *)arg1 + 0x60), (u8 *)arg0 + 0x2C, *(s32 *)((u8 *)arg0 + 0x20)
);
            temp_2 = *(s32 **)((u8 *)arg0 + 0x4C);
            if (temp_2 != NULL && *temp_2 == 0x19) {
                return 0;
            }
            return *(s32 *)((u8 *)arg0 + 0x28) = 1;
        }
        return 1;
    }
    return 0;
}
