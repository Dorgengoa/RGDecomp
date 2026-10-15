#include "types.h"

extern s32 D_00510010[];
extern s32 D_00510040[];
extern s32 D_005103D0[];

extern void *func_367F30(void);
extern void  factory_FactorySetFloorDefs_504190(void *h, s32 *t, s32 n);
extern void  factory_FactorySetBeltTileDefs_504170(void *h, s32 *t, s32 n);
extern void  factory_FactorySetPartDefs_504180(void *h, s32 *t, s32 n);

s32 factory_FactoryRegisterDefTables_505d60(void)
{
    void *h;

    h = func_367F30();
    if (h == 0) {
        return 0;
    }
    factory_FactorySetFloorDefs_504190(h, D_00510010, D_00510010 ? 2 : 0);
    factory_FactorySetBeltTileDefs_504170(h, D_00510040, D_00510040 ? 6 : 0);
    factory_FactorySetPartDefs_504180(h, D_005103D0, D_005103D0 ? 0x13 : 0);
    return 1;
}
