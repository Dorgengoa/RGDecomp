/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialIsInputActive_4e9f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x1F]; u8 f1F; } S;

extern S *D_00484A58;

u8 factory_FactoryMaterialIsInputActive_4e9f00(void)
{
    if (D_00484A58 != 0) {
        return D_00484A58->f1F;
    }
    return 0;
}
