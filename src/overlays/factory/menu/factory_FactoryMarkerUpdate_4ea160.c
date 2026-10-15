#include "types.h"

extern void *D_00484A60;
extern void  factory_FactoryMarkerUpdateSlot_4f6ef0(void *o, s32 a, s32 b, s32 c, s32 d);

void factory_FactoryMarkerUpdate_4ea160(s32 a, s32 b, s32 c, s32 d)
{
    if (D_00484A60 != 0) {
        factory_FactoryMarkerUpdateSlot_4f6ef0(D_00484A60, a, b, c, d);
    }
}
