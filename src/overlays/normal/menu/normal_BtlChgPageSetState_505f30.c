#include "types.h"
/* normal 0x00505F30 -- fetch-then-use guard.  The call goes through
 * normal_thunk_EXT_FUN_00289B40; the `bnel` skips a `return 0` body and its
 * delay slot already marshals $4 for the second call. */
extern void *normal_UiPageGetStateMachine_289b40(void *p);
extern void  func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgPageSetState_505f30(void *p, s32 id)
{
    void *w = normal_UiPageGetStateMachine_289b40(p);
    if (w == 0) {
        return 0;
    }
    func_28EDE0(w, id, 0);
    return 1;
}
