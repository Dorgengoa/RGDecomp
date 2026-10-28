/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerUpdate_4ea160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484A60;
/*rgp*/

void factory_FactoryMarkerUpdate_4ea160(s32 a, s32 b, s32 c, s32 d)
{
    if (D_00484A60 != 0) {
        factory_FactoryMarkerUpdateSlot_4f6ef0(D_00484A60, a, b, c, d);
    }
}
