/* rgp:protos */
#define RGP_SELF_normal_UiPageGetLayout_289b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal thunk -> func_289B60 -- a pass-through tail call; mwcc -O4 emits
 * `j` with an empty delay slot. */
/*rgp*/

void *normal_UiPageGetLayout_289b60(void *p)
{
    return UiPageGetLayout_289b60(p);
}
