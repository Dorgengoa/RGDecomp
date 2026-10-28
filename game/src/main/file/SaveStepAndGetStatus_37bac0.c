/* rgp:protos */
#define RGP_SELF_SaveStepAndGetStatus_37bac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void *memcpy(void *, const void *, s32);
extern void *D_004831D0;
extern u8 D_004E90F0[0x400];
extern u8 D_004E910C[0xC];
extern s32 D_004E9118[4];

s32 SaveStepAndGetStatus_37bac0(void **arg0)
{
    if (D_004831D0 == NULL) {
        return 0;
    }
    D_004E9118[0] = SaveModeDispatch_375df0(D_004831D0);
    memcpy(D_004E90F0,
           (u8 *)D_004831D0 + (*(s16 *)((u8 *)D_004831D0 + 0x4EC) * 0x1C) + 0x4A4,
           0x1C);
    memcpy(D_004E910C, SaveMgrGetResult_375a00(D_004831D0), 0xC);
    if (arg0 != NULL) {
        *arg0 = D_004E90F0;
    }
    return 1;
}
