/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_Vif1IntcHandler_15e170 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "eekernel.h"

extern s32 D_0047DF14;
extern s32 D_004810B0;
extern s32 D_004810B4;
extern s32 iSignalSema(s32 sema_id);

s32 Vif1IntcHandler_15e170(s32 cause)
{
    if (cause == 5) {
        if (D_0047DF14 >= 0) {
            D_004810B4 = ((s32)rg_logic_t0_count());
            iSignalSema(D_0047DF14);
            rg_vif1_fbrst_w32(8);
        }
        D_004810B0++;
    }
    ExitHandler();
    return 0;
}
