#include "types.h"

extern void *D_00484A4C;
extern void  factory_FactoryPartsSelChanged_4f0830(void *o);

s32 factory_FactoryPartsSelChangedCb_4ec950(void)
{
    factory_FactoryPartsSelChanged_4f0830(D_00484A4C);
    return 1;
}
