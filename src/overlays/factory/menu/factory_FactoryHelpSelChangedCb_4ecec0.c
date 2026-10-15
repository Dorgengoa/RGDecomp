#include "types.h"

extern void *D_00484A5C;
extern void  factory_FactoryHelpSelChanged_4f1c50(void *p);

s32 factory_FactoryHelpSelChangedCb_4ecec0(void)
{
    factory_FactoryHelpSelChanged_4f1c50(D_00484A5C);
    return 1;
}
