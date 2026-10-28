/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00455690[];
extern void IosBaseDtor_102970(void);
u32 D_0046FDA0[4] __attribute__((section(".data$rg0046FDA0"), aligned(16))) = {
    (u32)((u8*)&D_00455690 + 0x20u), @X@0046FDA4@, (u32)&IosBaseDtor_102970, @X@0046FDAC@
};
typedef char data2c_sizecheck_0046FDA0[(sizeof(D_0046FDA0) == 16) ? 1 : -1];
