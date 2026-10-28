/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D4A4[3] __attribute__((section(".data$rg0047D4A4"))) = {
    @F@0047D4A4@, @F@0047D4A8@, @F@0047D4AC@
};
typedef char data2c_sizecheck_0047D4A4[(sizeof(D_0047D4A4) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D4A8) "\n" RG_DR_ASYM(D_0047D4A8) " = " RG_DR_ASYM(D_0047D4A4) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D4AC) "\n" RG_DR_ASYM(D_0047D4AC) " = " RG_DR_ASYM(D_0047D4A4) " + 0x8\n"
);
