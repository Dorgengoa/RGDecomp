/* rgp:protos */
#define RGP_SELF_TaskStepEvent2_27ab80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

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
