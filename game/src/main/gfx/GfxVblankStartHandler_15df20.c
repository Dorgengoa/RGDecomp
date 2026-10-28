/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_GfxVblankStartHandler_15df20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "eekernel.h"

extern s32 D_004810C0;
extern s32 D_004810C4;
extern s32 D_004810C8;
extern void (*D_004810D0)(void);
extern s32 D_004810D4;
extern s32 D_0047DF18;
extern s32 iSignalSema(s32 sema_id);

s32 GfxVblankStartHandler_15df20(void)
{
    s32 n;

    D_004810D4 = 1;
    D_004810C8 = (u8)(((((u64)rg_gs_reg_r64(RG_GS_CSR)) >> 13 & 1) != 0) ^ 1);
    if (D_004810D0 != 0) {
        D_004810D0();
    }
    n = D_004810C4 + 1;
    D_004810C4 = n;
    if (n < 0) {
        D_004810C4 = 0;
    }
    D_004810D4 = 0;
    if (D_004810C0 != 0) {
        iSignalSema(D_0047DF18);
        D_004810C0 = 0;
    }
    ExitHandler();
    return 0;
}
