/* rgp:protos */
#define RGP_SELF_MenuItemIsDisabled_2a0270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MenuItemIsDisabled_2a0270(s32 arg0, void *arg1)
{
    s32 temp_16;

    temp_16 = *(s8 *)((u8 *)*(void **)((u8 *)arg1 + 0x10) + 2);
    if (((unsigned char)ItemRecKindIs6_3d4510(arg1)) != 0 || ((unsigned char)ItemRecKindIs12_3d45f0(arg1)) != 0 || temp_16 == 0xE) {
        return 1;
    }
    return 0;
}
