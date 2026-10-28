/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
extern void OstreamVirtualDtorThunk_1067f0(void);
u32 D_0046FECC[5] __attribute__((section(".data$rg0046FECC"))) = {
    (u32)((u8*)&D_004556F0 + 0x2D8u), @X@0046FED0@, (u32)&OstreamVirtualDtorThunk_1067f0, @X@0046FED8@, @X@0046FEDC@
};
typedef char data2c_sizecheck_0046FECC[(sizeof(D_0046FECC) == 20) ? 1 : -1];
