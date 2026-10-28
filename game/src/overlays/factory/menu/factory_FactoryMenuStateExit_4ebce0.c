/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuStateExit_4ebce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8    D_00484A6C;
/*rgp*/
/*rgp*/

s32 factory_FactoryMenuStateExit_4ebce0(void)
{
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    D_00484A6C = 0;
    return 1;
}
