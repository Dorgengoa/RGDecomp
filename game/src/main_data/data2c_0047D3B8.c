/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D3B8[4] __attribute__((section(".data$rg0047D3B8"), aligned(8))) = {
    @F@0047D3B8@, @F@0047D3BC@, @F@0047D3C0@, @F@0047D3C4@
};
typedef char data2c_sizecheck_0047D3B8[(sizeof(D_0047D3B8) == 16) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D3BC) "\n" RG_DR_ASYM(D_0047D3BC) " = " RG_DR_ASYM(D_0047D3B8) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D3C0) "\n" RG_DR_ASYM(D_0047D3C0) " = " RG_DR_ASYM(D_0047D3B8) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D3C4) "\n" RG_DR_ASYM(D_0047D3C4) " = " RG_DR_ASYM(D_0047D3B8) " + 0xC\n"
);
