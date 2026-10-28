/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_SysInitHardware_15e670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The `pcpyld` is mwcc materialising the 64-bit mask; the read-modify-write is
   a plain 64-bit `&=` on the GS privileged register at 0x12000000. */

extern void sceSifInitRpc_119b60(s32 x);
/*rgp*/
/*rgp*/
extern void sceDmaReset(s32 mode);
extern void sceGsResetPath(void);
extern void sceGsSyncV(s32 x);
extern void sceGsResetGraph_108110(s32 a, s32 b, s32 c, s32 d);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void SysInitHardware_15e670(void)
{
    sceSifInitRpc_119b60(0);
    CdInitDvdMode_15e5d0(0, 0, 0, 0);
    IopRebootWithImage_15e560();
    sceDmaReset(1);
    sceGsResetPath();
    sceGsSyncV(0);
    sceGsResetGraph_108110(0, 1, 2, 1);
    rg_gs_reg_w64(RG_GS_PMODE, ((u64)rg_gs_reg_r64(RG_GS_PMODE)) & ~3LL);
    GsClearDoubleBuffers_15e600();
    LoadIopModules_15e240();
    PadOpenPorts_1c6bf0();
    CdDiscInit_1c3130();
}
