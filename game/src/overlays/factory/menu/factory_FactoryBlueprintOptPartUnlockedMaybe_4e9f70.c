/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintOptPartUnlockedMaybe_4e9f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x6C]; u8 f6C; } S;

extern S *D_00484A48;

u8 factory_FactoryBlueprintOptPartUnlockedMaybe_4e9f70(void)
{
    if (D_00484A48 != 0) {
        return D_00484A48->f6C;
    }
    return 0;
}
