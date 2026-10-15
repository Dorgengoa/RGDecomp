#include "types.h"

extern s64 UModDi3_13a430(s32 a, s32 b);
extern s32 FloatToU64_13acb8(f32 a);
extern s32 GetCurrentScene_1f5be0(void);
extern void EventFireTriggers_3e2660(void *a, s32 b);
extern void ActionPacketInitIntervalTrigger_3e2b20(void *a, s32 b, s32 c);
extern void ActionPacketReset_3e3d00(void *a);
extern f32 D_0045B078[4];
extern s32 D_00483990;
extern s16 D_004839B0;

void EventFireIntervalTriggers_3e0220(s32 arg0) {
    u8 sp30[0x30];
    s32 temp_17;
    s16 temp_16;

    if (D_00483990 != 0) {
        temp_16 = (s16)UModDi3_13a430(arg0, FloatToU64_13acb8(D_0045B078[0]));
        if (temp_16 == 0 || temp_16 < D_004839B0) {
            temp_17 = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(sp30);
            ActionPacketInitIntervalTrigger_3e2b20(sp30, temp_17, 0x38);
            EventFireTriggers_3e2660(sp30, 0);
        }
        D_004839B0 = temp_16;
    }
}
