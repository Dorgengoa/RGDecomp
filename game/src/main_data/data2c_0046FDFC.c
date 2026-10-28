/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
extern void WostreamVirtualDtorThunk_106810(void);
u32 D_0046FDFC[5] __attribute__((section(".data$rg0046FDFC"))) = {
    (u32)((u8*)&D_004556F0 + 0x128u), @X@0046FE00@, (u32)&WostreamVirtualDtorThunk_106810, @X@0046FE08@, @X@0046FE0C@
};
typedef char data2c_sizecheck_0046FDFC[(sizeof(D_0046FDFC) == 20) ? 1 : -1];
