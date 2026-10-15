#include "types.h"
/* normal thunk -> func_289B50 -- a pass-through tail call; mwcc -O4 emits
 * `j` with an empty delay slot. */
extern void *func_289B50(void *p);

void *normal_UiPageGetList_289b50(void *p)
{
    return func_289B50(p);
}
