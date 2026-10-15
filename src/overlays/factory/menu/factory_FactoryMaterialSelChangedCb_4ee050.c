#include "types.h"

extern void *D_00484A58;
extern void  factory_FactoryMaterialShowCellInfo_4f38f0(void *p);

s32 factory_FactoryMaterialSelChangedCb_4ee050(void)
{
    factory_FactoryMaterialShowCellInfo_4f38f0(D_00484A58);
    return 1;
}
