/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DA0C[7] __attribute__((section(".data$rg0047DA0C"))) = {
    @F@0047DA0C@, @F@0047DA10@, @F@0047DA14@, @F@0047DA18@, @F@0047DA1C@, @F@0047DA20@, @F@0047DA24@
};
typedef char data2c_sizecheck_0047DA0C[(sizeof(D_0047DA0C) == 28) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DA10) "\n" RG_DR_ASYM(D_0047DA10) " = " RG_DR_ASYM(D_0047DA0C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DA14) "\n" RG_DR_ASYM(D_0047DA14) " = " RG_DR_ASYM(D_0047DA0C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DA18) "\n" RG_DR_ASYM(D_0047DA18) " = " RG_DR_ASYM(D_0047DA0C) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DA1C) "\n" RG_DR_ASYM(D_0047DA1C) " = " RG_DR_ASYM(D_0047DA0C) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DA20) "\n" RG_DR_ASYM(D_0047DA20) " = " RG_DR_ASYM(D_0047DA0C) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047DA24) "\n" RG_DR_ASYM(D_0047DA24) " = " RG_DR_ASYM(D_0047DA0C) " + 0x18\n"
);
