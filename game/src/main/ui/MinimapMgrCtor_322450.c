/* rgp:protos */
#define RGP_SELF_MinimapMgrCtor_322450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void *MinimapMgrCtor_322450(void *p)
{
    ConstructArray_100620(p, (void *)MinimapSlotCtor_322610, (void *)MinimapSlotDtor_3225c0, 0x1B0, 3);
    return p;
}
