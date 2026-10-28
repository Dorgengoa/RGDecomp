/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void WStreambufXsgetn_103d50(void);
extern void WStreambufXsputn_103b00(void);
u32 D_0046FE10[16] __attribute__((section(".data$rg0046FE10"), aligned(16))) = {
    (u32)((u8*)&D_004556F0 + 0x170u), @X@0046FE14@, (u32)&WStreambufDtor_1036b0, (u32)&WStreambufSetbuf_102a30, (u32)&WStreambufSeekoff_103f40, (u32)&WStreambufSeekpos_103f30, (u32)&WStreambufSync_1037d0, (u32)&WStreambufShowmanyc_1037e0, (u32)&WStreambufXsgetn_103d50, (u32)&WStreambufUnderflow_103d40, (u32)&WStreambufUflow_103cf0, (u32)&WStreambufPbackfail_103ce0, (u32)&WStreambufXsputn_103b00, (u32)&WStreambufOverflow_103af0, @X@0046FE48@, @X@0046FE4C@
};
typedef char data2c_sizecheck_0046FE10[(sizeof(D_0046FE10) == 64) ? 1 : -1];
