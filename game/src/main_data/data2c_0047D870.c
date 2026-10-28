/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D870[7] __attribute__((section(".data$rg0047D870"), aligned(16))) = {
    @F@0047D870@, @F@0047D874@, @F@0047D878@, @F@0047D87C@, @F@0047D880@, @F@0047D884@, @F@0047D888@
};
typedef char data2c_sizecheck_0047D870[(sizeof(D_0047D870) == 28) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D874) "\n" RG_DR_ASYM(D_0047D874) " = " RG_DR_ASYM(D_0047D870) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D878) "\n" RG_DR_ASYM(D_0047D878) " = " RG_DR_ASYM(D_0047D870) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D87C) "\n" RG_DR_ASYM(D_0047D87C) " = " RG_DR_ASYM(D_0047D870) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D880) "\n" RG_DR_ASYM(D_0047D880) " = " RG_DR_ASYM(D_0047D870) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D884) "\n" RG_DR_ASYM(D_0047D884) " = " RG_DR_ASYM(D_0047D870) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D888) "\n" RG_DR_ASYM(D_0047D888) " = " RG_DR_ASYM(D_0047D870) " + 0x18\n"
);
