/* rg-override: replaces game/src/main/gfx/GfxVblankStartHandler_15df20.c sha256 fd784b930c87cbbe36ce4e8c874dfb5ae4e79410a12ef2e4959a3f61784edbda
 * why: the snapshot C (d784320c de-asm) declares the handler and the callback D_004810D0 with no
 * argument; retail passes $a0 (the INTC cause) through to the callback (jalr). Kept from the
 * retail-listing port: the GS CSR read (rg_gs_reg_r64, port/hwaccess.h), handler-context kernel calls, `ei` = EIntr() */
#include "types.h"

/* VBLANK_START handler, installed by GfxSysInit_15dd20 through
 * sceGsSyncVCallback_109b18, so the kernel calls it as fn(cause) in handler
 * context (docs/KERNEL.md).  gp = 0x485170:
 *   D_004810D4 (gp-0x409C)  busy flag, 1 while the handler runs
 *   D_004810D0 (gp-0x40A0)  optional per-vblank callback (SetVblankCallback_15df10)
 *   D_004810C8 (gp-0x40A8)  1 = GS CSR.FIELD (bit 13) is 0
 *   D_004810C4 (gp-0x40AC)  vblank counter (GetVsyncCount_15df00), wraps to 0 instead of negative
 *   D_004810C0 (gp-0x40B0)  "signal on next vblank" request (WaitVsyncCount_15de90)
 *   D_0047DF18 (gp-0x7258)  its semaphore */
extern s32 D_004810C0;
extern s32 D_004810C4;
extern s32 D_004810C8;
extern s32 D_004810D0;
extern s32 D_004810D4;
extern s32 D_0047DF18;
extern s32 iSignalSema(s32 sema_id);
extern s32 EIntr(void);

s32 GfxVblankStartHandler_15df20(s32 cause)
{
    s32 cb;
    s32 n;

    D_004810D4 = 1;
    /* ld CSR; dsrl 13; andi 1; sltu; xori 1 */
    D_004810C8 = ((rg_gs_reg_r64(RG_GS_CSR) >> 13) & 1) == 0;
    cb = D_004810D0;
    if (cb != 0)
        ((void (*)(s32))(unsigned long)(u32)cb)(cause); /* jalr $2, $a0 still = cause */
    n = D_004810C4 + 1;
    D_004810C4 = n;
    if (n < 0)
        D_004810C4 = 0;
    D_004810D4 = 0; /* in the delay slot: cleared before the signal */
    if (D_004810C0 != 0) {
        iSignalSema(D_0047DF18);
        D_004810C0 = 0;
    }
    EIntr(); /* sync; ei */
    return 0;
}
