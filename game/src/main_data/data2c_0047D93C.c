/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D93C[4] __attribute__((section(".data$rg0047D93C"))) = {
    @F@0047D93C@, @F@0047D940@, @F@0047D944@, @F@0047D948@
};
typedef char data2c_sizecheck_0047D93C[(sizeof(D_0047D93C) == 16) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D940) "\n" RG_DR_ASYM(D_0047D940) " = " RG_DR_ASYM(D_0047D93C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D944) "\n" RG_DR_ASYM(D_0047D944) " = " RG_DR_ASYM(D_0047D93C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D948) "\n" RG_DR_ASYM(D_0047D948) " = " RG_DR_ASYM(D_0047D93C) " + 0xC\n"
);
