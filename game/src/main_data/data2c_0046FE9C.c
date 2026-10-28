/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
extern void IstreamVirtualDtorThunk_106800(void);
u32 D_0046FE9C[3] __attribute__((section(".data$rg0046FE9C"))) = {
    (u32)((u8*)&D_004556F0 + 0x278u), @X@0046FEA0@, (u32)&IstreamVirtualDtorThunk_106800
};
typedef char data2c_sizecheck_0046FE9C[(sizeof(D_0046FE9C) == 12) ? 1 : -1];
