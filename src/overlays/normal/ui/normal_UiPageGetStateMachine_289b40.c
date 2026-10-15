#include "types.h"
/* normal thunk -> func_289B40 -- a pass-through tail call; mwcc -O4 emits
 * `j` with an empty delay slot. */
extern void *func_289B40(void *p);

void *normal_UiPageGetStateMachine_289b40(void *p)
{
    return func_289B40(p);
}
