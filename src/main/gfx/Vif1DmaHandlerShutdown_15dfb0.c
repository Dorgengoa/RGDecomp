#include "types.h"

extern void DeleteSema(s32);
extern void sceDmaSync_10a2e0(s32, s32, s32);
extern void DisableIntc_117080(s32);
extern void Vif1DmaStart_15e070(s32);
extern void RemoveIntcHandler(s32, s32);
extern void SignalSema(s32);
extern void WaitSema(s32);
s32 sceDmaGetChan(s32);

extern s32 D_0047DF10;
extern s32 D_0047DF14;
extern s32 D_004810A8;
extern s32 D_004810AC;
extern u8 D_004810B8;
extern s32 D_004810BC;

void Vif1DmaHandlerShutdown_15dfb0(void) {
    volatile s32 sp1C;

    if ((D_004810B8 != 0) && (D_004810BC != 0)) {
        Vif1DmaStart_15e070(D_004810BC);
        D_004810BC = 0;
    }
    sp1C = D_0047DF10;
    WaitSema(D_0047DF10);
    if (D_004810AC == 0) {
        SignalSema(sp1C);
        return;
    }
    if (D_0047DF14 >= 0) {
        WaitSema(D_0047DF14);
        DeleteSema(D_0047DF14);
        RemoveIntcHandler(5, D_004810A8);
        D_004810A8 = -1;
        D_0047DF14 = -1;
    }
    DisableIntc_117080(5);
    sceDmaSync_10a2e0(sceDmaGetChan(1), 0, 0);
    D_004810AC = 0;
    SignalSema(sp1C);
}
