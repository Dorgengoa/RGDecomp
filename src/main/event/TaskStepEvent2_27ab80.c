#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetCurEventPlayer_26b830(void);
extern void EventPlayerCastFrameAnimUpdateMaybe_249a60(s32, s32);

void TaskStepEvent2_27ab80(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCurrentScene_1f5be0();
    r1 = GetCurEventPlayer_26b830();
    if (r1 != 0) {
        EventPlayerCastFrameAnimUpdateMaybe_249a60(r1, r0);
    }
}
