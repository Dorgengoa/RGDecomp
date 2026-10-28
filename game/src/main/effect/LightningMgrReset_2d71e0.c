/* rgp:protos */
#define RGP_SELF_LightningMgrReset_2d71e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void LightningMgrReset_2d71e0(u8 *p)
{
    s32 i;

    LightningMgrCtorMaybe_2d6490(p);
    for (i = 0; i < 16; i++) {
        *(s16 *)(p + i * 48 + 0x3A) = 0;
    }
}
