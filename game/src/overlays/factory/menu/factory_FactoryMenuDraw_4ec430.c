/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuDraw_4ec430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8    D_00484A68;
extern void *D_004807E4;
extern void *D_004807E8;
extern void *D_004807EC;
/*rgp*/

void factory_FactoryMenuDraw_4ec430(void)
{
    if (D_00484A68 != 0) {
        UiDrawWidgets_291910(D_004807E4);
        UiDrawWidgets_291910(D_004807E8);
        UiDrawWidgets_291910(D_004807EC);
    }
}
