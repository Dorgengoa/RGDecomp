/* rgp:protos */
#define RGP_SELF_InvAddItemAtSlot_3c64c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void * InvAddItemAtSlot_3c64c0(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    return InvAddItemCoreMaybe_3c6540(a, b, InvGetCategoryOfId_3d56f0(c), d, c, e, 0);
}
