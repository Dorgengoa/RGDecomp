/* rgp:protos */
#define RGP_SELF_IopRebootWithImage_15e560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00458CC0[];
extern s32 sceSifRebootIop_11fcd0(void *p);
extern s32 sceSifSyncIop_11fc80(void);
extern void sceSifInitRpc_119b60(s32 x);
extern void sceSifInitIopHeap(void);
/*rgp*/
/*rgp*/

void IopRebootWithImage_15e560(void)
{
    while (!sceSifRebootIop_11fcd0(D_00458CC0)) {
    }
    while (!sceSifSyncIop_11fc80()) {
    }
    sceSifInitRpc_119b60(0);
    sceSifInitIopHeap();
    CdInitDvdMode_15e5d0(0, 0, 0, 0);
    sceFsReset();
}
