/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialSelChangedCb_4ee050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484A58;
/*rgp*/

s32 factory_FactoryMaterialSelChangedCb_4ee050(void)
{
    factory_FactoryMaterialShowCellInfo_4f38f0(D_00484A58);
    return 1;
}
