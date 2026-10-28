/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DA44[10] __attribute__((section(".data$rg0047DA44"))) = {
    @F@0047DA44@, @F@0047DA48@, @F@0047DA4C@, @F@0047DA50@, @F@0047DA54@, @F@0047DA58@, @F@0047DA5C@, @F@0047DA60@, @F@0047DA64@, @F@0047DA68@
};
typedef char data2c_sizecheck_0047DA44[(sizeof(D_0047DA44) == 40) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DA48) "\n" RG_DR_ASYM(D_0047DA48) " = " RG_DR_ASYM(D_0047DA44) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DA4C) "\n" RG_DR_ASYM(D_0047DA4C) " = " RG_DR_ASYM(D_0047DA44) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DA50) "\n" RG_DR_ASYM(D_0047DA50) " = " RG_DR_ASYM(D_0047DA44) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DA54) "\n" RG_DR_ASYM(D_0047DA54) " = " RG_DR_ASYM(D_0047DA44) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DA58) "\n" RG_DR_ASYM(D_0047DA58) " = " RG_DR_ASYM(D_0047DA44) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047DA5C) "\n" RG_DR_ASYM(D_0047DA5C) " = " RG_DR_ASYM(D_0047DA44) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047DA60) "\n" RG_DR_ASYM(D_0047DA60) " = " RG_DR_ASYM(D_0047DA44) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047DA64) "\n" RG_DR_ASYM(D_0047DA64) " = " RG_DR_ASYM(D_0047DA44) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047DA68) "\n" RG_DR_ASYM(D_0047DA68) " = " RG_DR_ASYM(D_0047DA44) " + 0x24\n"
);
