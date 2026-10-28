/* rgp:protos */
#define RGP_SELF_CharaEventLogTimersTick_3a6220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void CharaEventLogTimersTick_3a6220(s32 arg0, f32 fparg0) {
    f32 v;
    s32 i;
    u8 *rec;
    u8 *sub;

    i = 0;
    do {
        rec = (u8 *)arg0 + i * 8;
        sub = rec + 0x248;
        if (*(s16 *)(rec + 0x248) >= 0) {
            v = *(f32 *)(sub + 4);
            if (!(v <= 0.0f)) {
                v = v - fparg0;
                *(f32 *)(sub + 4) = v;
                if (v <= 0.0f) {
                    CharaEventLogTimerReset_3a6940(sub);
                }
            }
        }
        i += 1;
    } while (i < 0x10);
}
