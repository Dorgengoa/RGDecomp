#include "types.h"

extern void ViBufSetD4Chcr_1d47a0(s32);
extern void ViBufSetD3Chcr_1d4800(s32);
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
    arg0->f1C = *(volatile s32 *)0x1000B410;
    arg0->f20 = *(volatile s32 *)0x1000B430;
    arg0->f24 = *(volatile s32 *)0x1000B420;
    arg0->f28 = *(volatile s32 *)0x1000B400;
    while (*(volatile s32 *)0x10002010 & 0xF0) {
    }
    ViBufSetD3Chcr_1d4800(0);
    arg0->f2C = *(volatile s32 *)0x1000B010;
    arg0->f30 = *(volatile s32 *)0x1000B020;
    arg0->f34 = *(volatile s32 *)0x1000B000;
    arg0->f38 = *(volatile s32 *)0x10002020;
    arg0->f3C = *(volatile s32 *)0x10002010;
    SignalSema(arg0->sema);
    return 1;
}
