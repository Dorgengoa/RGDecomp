/* rgp:protos */
#define RGP_SELF_Vif1DmaStart_15e070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 AddIntcHandler(s32 cause, void *handler, s32 arg);
extern s32 CreateSema(void *param);
extern void sceDmaSend_10a040(u8 *arg0, s32 arg1);
extern void EnableIntc_1170e8(s32 arg0);
extern void FlushCache(s32 arg0);
extern void SignalSema(s32 arg0);
extern void WaitSema(s32 arg0);
extern u8 *sceDmaGetChan(s32 arg0);
extern s32 D_0047DF10;
extern s32 D_0047DF14;
extern s32 D_004810A8;
extern s32 D_004810AC;
extern s32 D_004810B0;
extern u8 D_004810B8;
extern s32 D_004810BC;
/*rgp*/

typedef struct { u8 lo : 6; u8 f : 1; u8 hi : 1; } Chcr;
void Vif1DmaStart_15e070(s32 arg0)
{
    volatile s32 sp4C;
    s32 sp30[6] __attribute__((aligned(16)));
    u8 *p;

    sp4C = D_0047DF10;
    WaitSema(D_0047DF10);
    if (D_004810B8 != 0 && D_004810BC == 0) {
        D_004810BC = arg0;
        SignalSema(sp4C);
        return;
    }
    if (D_004810AC != 0) {
        SignalSema(sp4C);
        return;
    }
    D_004810B0 = 0;
    p = sceDmaGetChan(1);
    ((Chcr *)p)->f = 1;
    FlushCache(0);
    sceDmaSend_10a040(p, arg0);
    sp30[1] = 1;
    sp30[2] = 0;
    sp30[5] = 0;
    D_0047DF14 = CreateSema(sp30);
    D_004810AC = 1;
    D_004810A8 = AddIntcHandler(5, Vif1IntcHandler_15e170, -1);
    EnableIntc_1170e8(5);
    SignalSema(sp4C);
}
