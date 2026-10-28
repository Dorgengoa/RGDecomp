/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_004556F0[];
/*rgp*/
extern void WFilebufOverflow_1053e0(void);
extern void WFilebufPbackfail_105830(void);
extern void WFilebufSeekoff_105250(void);
extern void WFilebufSeekpos_105140(void);
/*rgp*/
/*rgp*/
/*rgp*/
extern void WFilebufUflow_105900(void);
extern void WFilebufUnderflow_105a30(void);
extern void WStreambufXsgetn_103d50(void);
extern void WStreambufXsputn_103b00(void);
u32 D_0046FE50[16] __attribute__((section(".data$rg0046FE50"), aligned(16))) = {
    (u32)((u8*)&D_004556F0 + 0x1C8u), @X@0046FE54@, (u32)&WFilebufDtor_1033c0, (u32)&WFilebufSetbuf_1037b0, (u32)&WFilebufSeekoff_105250, (u32)&WFilebufSeekpos_105140, (u32)&WFilebufSync_105090, (u32)&WFilebufShowmanyc_105bb0, (u32)&WStreambufXsgetn_103d50, (u32)&WFilebufUnderflow_105a30, (u32)&WFilebufUflow_105900, (u32)&WFilebufPbackfail_105830, (u32)&WStreambufXsputn_103b00, (u32)&WFilebufOverflow_1053e0, @X@0046FE88@, @X@0046FE8C@
};
typedef char data2c_sizecheck_0046FE50[(sizeof(D_0046FE50) == 64) ? 1 : -1];
