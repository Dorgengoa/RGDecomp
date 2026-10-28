/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DC7C[4] __attribute__((section(".data$rg0047DC7C"))) = {
    @F@0047DC7C@, @F@0047DC80@, @F@0047DC84@, @F@0047DC88@
};
typedef char data2c_sizecheck_0047DC7C[(sizeof(D_0047DC7C) == 16) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DC80) "\n" RG_DR_ASYM(D_0047DC80) " = " RG_DR_ASYM(D_0047DC7C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DC84) "\n" RG_DR_ASYM(D_0047DC84) " = " RG_DR_ASYM(D_0047DC7C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DC88) "\n" RG_DR_ASYM(D_0047DC88) " = " RG_DR_ASYM(D_0047DC7C) " + 0xC\n"
);
