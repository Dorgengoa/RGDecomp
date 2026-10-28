/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D8AC[12] __attribute__((section(".data$rg0047D8AC"))) = {
    @F@0047D8AC@, @F@0047D8B0@, @F@0047D8B4@, @F@0047D8B8@, @F@0047D8BC@, @F@0047D8C0@, @F@0047D8C4@, @F@0047D8C8@, @F@0047D8CC@, @F@0047D8D0@, @F@0047D8D4@, @F@0047D8D8@
};
typedef char data2c_sizecheck_0047D8AC[(sizeof(D_0047D8AC) == 48) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D8B0) "\n" RG_DR_ASYM(D_0047D8B0) " = " RG_DR_ASYM(D_0047D8AC) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D8B4) "\n" RG_DR_ASYM(D_0047D8B4) " = " RG_DR_ASYM(D_0047D8AC) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D8B8) "\n" RG_DR_ASYM(D_0047D8B8) " = " RG_DR_ASYM(D_0047D8AC) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D8BC) "\n" RG_DR_ASYM(D_0047D8BC) " = " RG_DR_ASYM(D_0047D8AC) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D8C0) "\n" RG_DR_ASYM(D_0047D8C0) " = " RG_DR_ASYM(D_0047D8AC) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D8C4) "\n" RG_DR_ASYM(D_0047D8C4) " = " RG_DR_ASYM(D_0047D8AC) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047D8C8) "\n" RG_DR_ASYM(D_0047D8C8) " = " RG_DR_ASYM(D_0047D8AC) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047D8CC) "\n" RG_DR_ASYM(D_0047D8CC) " = " RG_DR_ASYM(D_0047D8AC) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047D8D0) "\n" RG_DR_ASYM(D_0047D8D0) " = " RG_DR_ASYM(D_0047D8AC) " + 0x24\n"
    ".globl " RG_DR_ASYM(D_0047D8D4) "\n" RG_DR_ASYM(D_0047D8D4) " = " RG_DR_ASYM(D_0047D8AC) " + 0x28\n"
    ".globl " RG_DR_ASYM(D_0047D8D8) "\n" RG_DR_ASYM(D_0047D8D8) " = " RG_DR_ASYM(D_0047D8AC) " + 0x2C\n"
);
