/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetState_506b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506B70 -- the `bnel` delay slot moves the handle into $4 for the
 * guarded call; $16 holds the id across func_289B40. */
/*rgp*/
/*rgp*/
extern s32 normal_LeaderHudSetState_506b70(void *p, s32 id);
s32 normal_LeaderHudSetState_506b70(void *p, s32 id)
{
    void *w = UiPageGetStateMachine_289b40(p);
    if (w == 0) {
        return 0;
    }
    StateMachineSetState_28ede0(w, id, 0);
    return 1;
}
