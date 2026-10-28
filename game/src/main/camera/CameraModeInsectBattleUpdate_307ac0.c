/* rgp:protos */
#define RGP_SELF_CameraModeInsectBattleUpdate_307ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Fetches a handle and, if there is one, calls into the overlay. func_4F2100
   is not in the main image at all: 0x004F2100 is overlay territory and the
   address is defined absolutely in SCUS_974.90.lcf, so the extern resolves at
   link time exactly as the reference assembly's `jal` does. */

/*rgp*/
extern void func_4F2100(s32 handle);

void CameraModeInsectBattleUpdate_307ac0(void)
{
    s32 handle;

    handle = InsectBattleGet_31a8d0();
    if (handle != 0) {
        func_4F2100(handle);
    }
}
