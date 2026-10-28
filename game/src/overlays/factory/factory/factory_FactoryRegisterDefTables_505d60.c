/* rgp:protos */
#define RGP_SELF_factory_FactoryRegisterDefTables_505d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 factory_D_00510010[];
extern s32 factory_D_00510040[];
extern s32 factory_D_005103D0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryRegisterDefTables_505d60(void)
{
    void *h;

    h = GetFactoryObj_367f30();
    if (h == 0) {
        return 0;
    }
    factory_FactorySetFloorDefs_504190(h, factory_D_00510010, factory_D_00510010 ? 2 : 0);
    factory_FactorySetBeltTileDefs_504170(h, factory_D_00510040, factory_D_00510040 ? 6 : 0);
    factory_FactorySetPartDefs_504180(h, factory_D_005103D0, factory_D_005103D0 ? 0x13 : 0);
    return 1;
}
