/* rgp:protos */
#define RGP_SELF_EventFireIntervalTriggers_3e0220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B078[4];
extern s32 D_00483990;
extern s16 D_004839B0;

void EventFireIntervalTriggers_3e0220(long long arg0) {
    u8 sp30[0x30] __attribute__((aligned(16)));
    s32 temp_17;
    s16 temp_16;

    if (D_00483990 != 0) {
        temp_16 = (s16)UModDi3_13a430((unsigned long long)(arg0), (unsigned long long)(FloatToU64_13acb8(D_0045B078[0])));
        if (temp_16 == 0 || temp_16 < D_004839B0) {
            temp_17 = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(sp30);
            ActionPacketInitIntervalTrigger_3e2b20(sp30, temp_17, 0x38);
            EventFireTriggers_3e2660(sp30, 0);
        }
        D_004839B0 = temp_16;
    }
}
