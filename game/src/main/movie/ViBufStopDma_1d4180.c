/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_ViBufStopDma_1d4180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void SignalSema(s32);
extern void WaitSema(s32);

typedef struct {
    u8 pad00[0x1C];
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 sema;
    s32 f44;
} S;

s32 ViBufStopDma_1d4180(S *arg0) {
    WaitSema(arg0->sema);
    arg0->f44 = 0;
    ViBufSetD4Chcr_1d47a0(5);
    arg0->f1C = ((s32)HW_R32(0x1000B410u));
    arg0->f20 = ((s32)HW_R32(0x1000B430u));
    arg0->f24 = ((s32)HW_R32(0x1000B420u));
    arg0->f28 = ((s32)HW_R32(0x1000B400u));
    while (((s32)HW_R32(0x10002010u)) & 0xF0) {
    }
    ViBufSetD3Chcr_1d4800(0);
    arg0->f2C = ((s32)HW_R32(0x1000B010u));
    arg0->f30 = ((s32)HW_R32(0x1000B020u));
    arg0->f34 = ((s32)HW_R32(0x1000B000u));
    arg0->f38 = ((s32)HW_R32(0x10002020u));
    arg0->f3C = ((s32)HW_R32(0x10002010u));
    SignalSema(arg0->sema);
    return 1;
}
