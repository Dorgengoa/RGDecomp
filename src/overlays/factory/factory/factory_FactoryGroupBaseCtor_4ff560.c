#include "types.h"

extern void factory_FactoryGroupBaseReset_4ff530(void *p);

void *factory_FactoryGroupBaseCtor_4ff560(void *p)
{
    factory_FactoryGroupBaseReset_4ff530(p);
    return p;
}
