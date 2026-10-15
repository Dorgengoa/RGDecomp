#include "types.h"

extern void *D_00484A48;
extern void  factory_FactoryBlueprintSelChanged_4fb3d0(void *o);

s32 factory_FactoryBlueprintSelChangedCb_4eef00(void)
{
    factory_FactoryBlueprintSelChanged_4fb3d0(D_00484A48);
    return 1;
}
