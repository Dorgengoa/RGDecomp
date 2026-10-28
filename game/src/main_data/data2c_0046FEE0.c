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
extern void StreambufXsgetn_1039b0(void);
extern void StreambufXsputn_103890(void);
u32 D_0046FEE0[16] __attribute__((section(".data$rg0046FEE0"), aligned(16))) = {
    (u32)((u8*)&D_004556F0 + 0x318u), @X@0046FEE4@, (u32)&StreambufDtor_103760, (u32)&StreambufSetbuf_102a40, (u32)&StreambufSeekoff_103ae0, (u32)&StreambufSeekpos_103ad0, (u32)&StreambufSync_1037f0, (u32)&StreambufShowmanyc_103800, (u32)&StreambufXsgetn_1039b0, (u32)&StreambufUnderflow_103810, (u32)&StreambufUflow_103820, (u32)&StreambufPbackfail_103870, (u32)&StreambufXsputn_103890, (u32)&StreambufOverflow_103880, @X@0046FF18@, @X@0046FF1C@
};
typedef char data2c_sizecheck_0046FEE0[(sizeof(D_0046FEE0) == 64) ? 1 : -1];
