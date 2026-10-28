/* rg-override: replaces game/src/main/gs/Vif0SendInitPacketMaybe_13bcc0.c sha256 2737a6d74d9832cb343f6d360cbd51ee7d60269ca536abe63ffb4eb51241f8bf
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void *sceDmaGetChan(s32 id);
extern void sceDmaSend_10a040(void *chan, void *tag);
extern u32 sceDmaSync_10a2e0(void *chan, s32 mode);

/* VIF0 init DMA chain in MAIN .data (data2c_00445810, 0x450 bytes). */
extern u8 D_00445810[];

/* Sends the VIF0 init chain on DMA channel 0 with TTE set and waits. */
void Vif0SendInitPacketMaybe_13bcc0(void)
{
    u8 *chan = (u8 *)sceDmaGetChan(0);
    /* CHCR-image byte at chan+0: TTE (bit 6) = 1 */
    chan[0] = (u8)((chan[0] & ~0x40) | 0x40);
    /* [port] address: retail passes the literal 0x00445810 (lui/addiu) */
    sceDmaSend_10a040(chan, D_00445810);
    /* retail passes a third argument ($6 = 0); the callee takes two */
    sceDmaSync_10a2e0(chan, 0);
}
