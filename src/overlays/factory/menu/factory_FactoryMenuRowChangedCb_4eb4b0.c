#include "types.h"

extern void *D_00484A44;
extern void  factory_FactoryMenuRowHighlight_4f0c80(void *o);

s32 factory_FactoryMenuRowChangedCb_4eb4b0(void)
{
    factory_FactoryMenuRowHighlight_4f0c80(D_00484A44);
    return 1;
}
