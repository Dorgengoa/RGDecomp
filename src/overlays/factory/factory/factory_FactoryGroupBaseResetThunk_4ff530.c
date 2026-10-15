#include "types.h"

/* factory.bin overlay, 0x004FF440 -- tail-call thunk for factory_FactoryGroupBaseReset_4ff530. */

extern void factory_FactoryGroupBaseReset_4ff530(void *o);

void factory_FactoryGroupBaseResetThunk_4ff530(void *o)
{
    factory_FactoryGroupBaseReset_4ff530(o);
}
