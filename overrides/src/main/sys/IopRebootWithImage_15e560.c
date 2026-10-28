/* rg-override: replaces game/src/main/sys/IopRebootWithImage_15e560.c sha256 12872f714a7299bce5cb5d1abcee6ba7b1013c83e23ec96faeb48b00445121bd
 * why: native IOP (docs/NATIVE-IOP.md, PLAN.md D9): with RG_IOP=native there is no IOP
 *      to reboot with IOPRP300.IMG, no SIF RPC to start, no IOP heap and no FILEIO
 *      client to reset; only the game's own DVD-mode init (CdInitDvdMode_15e5d0, the
 *      native-FS override) runs.  RG_IOP=hle: the original sequence. */
/* rgp:protos */
#define RGP_SELF_IopRebootWithImage_15e560 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_iop.h"

extern u8 D_00458CC0[];
extern s32 sceSifRebootIop_11fcd0(void *p);
extern s32 sceSifSyncIop_11fc80(void);
extern void sceSifInitRpc_119b60(s32 x);
extern void sceSifInitIopHeap(void);
/*rgp*/
/*rgp*/

void IopRebootWithImage_15e560(void)
{
    if (rg_iop_native()) {
        CdInitDvdMode_15e5d0(0, 0, 0, 0);
        return;
    }
    while (!sceSifRebootIop_11fcd0(D_00458CC0)) {
    }
    while (!sceSifSyncIop_11fc80()) {
    }
    sceSifInitRpc_119b60(0);
    sceSifInitIopHeap();
    CdInitDvdMode_15e5d0(0, 0, 0, 0);
    sceFsReset();
}
