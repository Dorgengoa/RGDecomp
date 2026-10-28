/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DCF4[10] __attribute__((section(".data$rg0047DCF4"))) = {
    @F@0047DCF4@, @F@0047DCF8@, @F@0047DCFC@, @F@0047DD00@, @F@0047DD04@, @F@0047DD08@, @F@0047DD0C@, @F@0047DD10@, @F@0047DD14@, @F@0047DD18@
};
typedef char data2c_sizecheck_0047DCF4[(sizeof(D_0047DCF4) == 40) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DCF8) "\n" RG_DR_ASYM(D_0047DCF8) " = " RG_DR_ASYM(D_0047DCF4) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DCFC) "\n" RG_DR_ASYM(D_0047DCFC) " = " RG_DR_ASYM(D_0047DCF4) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DD00) "\n" RG_DR_ASYM(D_0047DD00) " = " RG_DR_ASYM(D_0047DCF4) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DD04) "\n" RG_DR_ASYM(D_0047DD04) " = " RG_DR_ASYM(D_0047DCF4) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DD08) "\n" RG_DR_ASYM(D_0047DD08) " = " RG_DR_ASYM(D_0047DCF4) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047DD0C) "\n" RG_DR_ASYM(D_0047DD0C) " = " RG_DR_ASYM(D_0047DCF4) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047DD10) "\n" RG_DR_ASYM(D_0047DD10) " = " RG_DR_ASYM(D_0047DCF4) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047DD14) "\n" RG_DR_ASYM(D_0047DD14) " = " RG_DR_ASYM(D_0047DCF4) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047DD18) "\n" RG_DR_ASYM(D_0047DD18) " = " RG_DR_ASYM(D_0047DCF4) " + 0x24\n"
);
