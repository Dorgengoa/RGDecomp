/* rgp:protos */
#define RGP_SELF_SysVblankCallback_1c33a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00481558;

s32 SysVblankCallback_1c33a0(void)
{
    SysTickThreadSignalIsr_1c34f0();
    if (D_00481558 == 0) {
        CdDiskWatchWakeIsr_17ff10();
    }
    D_00481558 = D_00481558 + 1;
    if (D_00481558 >= 0x1E) {
        D_00481558 = 0;
    }
    return 0;
}
