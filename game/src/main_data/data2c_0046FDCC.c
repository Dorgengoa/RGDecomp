/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
extern void WistreamVirtualDtorThunk_106820(void);
u32 D_0046FDCC[3] __attribute__((section(".data$rg0046FDCC"))) = {
    (u32)((u8*)&D_004556F0 + 0xC8u), @X@0046FDD0@, (u32)&WistreamVirtualDtorThunk_106820
};
typedef char data2c_sizecheck_0046FDCC[(sizeof(D_0046FDCC) == 12) ? 1 : -1];
