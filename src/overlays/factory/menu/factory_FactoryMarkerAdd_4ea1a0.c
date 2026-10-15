#include "types.h"

extern void *D_00484A60;
extern s32   factory_FactoryMarkerAddSlot_4f6fe0(void *o, void *a);

s32 factory_FactoryMarkerAdd_4ea1a0(void *a)
{
    void *o;

    o = D_00484A60;
    return o != 0 ? factory_FactoryMarkerAddSlot_4f6fe0(o, a) : -1;
}
