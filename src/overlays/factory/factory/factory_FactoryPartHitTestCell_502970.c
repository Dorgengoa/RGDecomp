#include "types.h"

extern s32 factory_FactoryPartDefGridRectHitTest_4fe930(void *d, s32 b, s32 c, s32 e, s32 f);

s32 factory_FactoryPartHitTestCell_502970(s32 a, s32 b, s32 c, void *d, s32 e, s32 f)
{
    if (d != 0) {
        return factory_FactoryPartDefGridRectHitTest_4fe930(d, b, c, e, f);
    }
    return 0;
}
