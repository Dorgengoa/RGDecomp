/* rgp:protos */
#define RGP_SELF_normal_UiPageGetList_289b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal thunk -> func_289B50 -- a pass-through tail call; mwcc -O4 emits
 * `j` with an empty delay slot. */
/*rgp*/

void *normal_UiPageGetList_289b50(void *p)
{
    return UiPageGetList_289b50(p);
}
