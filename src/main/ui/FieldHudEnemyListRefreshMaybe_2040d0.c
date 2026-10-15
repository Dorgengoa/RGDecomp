#include "types.h"

extern u8 D_00527020[];

extern void func_4F1D40(void *);
extern void func_4F1A80(void *, s32);

void FieldHudEnemyListRefreshMaybe_2040d0(void)
{
    func_4F1D40(D_00527020);
    func_4F1A80(D_00527020, 1);
}
