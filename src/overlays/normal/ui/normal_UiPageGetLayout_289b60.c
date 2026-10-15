#include "types.h"
/* normal thunk -> func_289B60 -- a pass-through tail call; mwcc -O4 emits
 * `j` with an empty delay slot. */
extern void *func_289B60(void *p);

void *normal_UiPageGetLayout_289b60(void *p)
{
    return func_289B60(p);
}
