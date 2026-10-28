/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetState_505f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505F30 -- fetch-then-use guard.  The call goes through
 * normal_thunk_EXT_FUN_00289B40; the `bnel` skips a `return 0` body and its
 * delay slot already marshals $4 for the second call. */
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageSetState_505f30(void *p, s32 id)
{
    void *w = normal_UiPageGetStateMachine_289b40(p);
    if (w == 0) {
        return 0;
    }
    StateMachineSetState_28ede0(w, id, 0);
    return 1;
}
