#include "types.h"

extern void *D_00484A58;
extern void  factory_FactoryMaterialCursorBob_4f3a70(void *p, s32 a, s32 b);

s32 factory_FactoryMaterialChoiceCursorBobCb_4ed7b0(void)
{
    factory_FactoryMaterialCursorBob_4f3a70(D_00484A58, 0, 1);
    return 1;
}
