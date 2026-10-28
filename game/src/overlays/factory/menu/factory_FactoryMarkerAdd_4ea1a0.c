/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerAdd_4ea1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484A60;
/*rgp*/

s32 factory_FactoryMarkerAdd_4ea1a0(void *a)
{
    void *o;

    o = D_00484A60;
    return o != 0 ? factory_FactoryMarkerAddSlot_4f6fe0(o, a) : -1;
}
