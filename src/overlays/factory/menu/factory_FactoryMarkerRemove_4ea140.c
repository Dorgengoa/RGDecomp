#include "types.h"

extern void *D_00484A60;
extern s32   factory_FactoryMarkerRemoveSlot_4f6e50(void *o, s32 a, s32 b);

s32 factory_FactoryMarkerRemove_4ea140(s32 a, s32 b)
{
    return factory_FactoryMarkerRemoveSlot_4f6e50(D_00484A60, a, b);
}
