/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D90C[5] __attribute__((section(".data$rg0047D90C"))) = {
    @F@0047D90C@, @F@0047D910@, @F@0047D914@, @F@0047D918@, @F@0047D91C@
};
typedef char data2c_sizecheck_0047D90C[(sizeof(D_0047D90C) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D910) "\n" RG_DR_ASYM(D_0047D910) " = " RG_DR_ASYM(D_0047D90C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D914) "\n" RG_DR_ASYM(D_0047D914) " = " RG_DR_ASYM(D_0047D90C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D918) "\n" RG_DR_ASYM(D_0047D918) " = " RG_DR_ASYM(D_0047D90C) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D91C) "\n" RG_DR_ASYM(D_0047D91C) " = " RG_DR_ASYM(D_0047D90C) " + 0x10\n"
);
