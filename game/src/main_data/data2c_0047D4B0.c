/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D4B0[7] __attribute__((section(".data$rg0047D4B0"), aligned(16))) = {
    @F@0047D4B0@, @F@0047D4B4@, @F@0047D4B8@, @F@0047D4BC@, @F@0047D4C0@, @F@0047D4C4@, @F@0047D4C8@
};
typedef char data2c_sizecheck_0047D4B0[(sizeof(D_0047D4B0) == 28) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D4B4) "\n" RG_DR_ASYM(D_0047D4B4) " = " RG_DR_ASYM(D_0047D4B0) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D4B8) "\n" RG_DR_ASYM(D_0047D4B8) " = " RG_DR_ASYM(D_0047D4B0) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D4BC) "\n" RG_DR_ASYM(D_0047D4BC) " = " RG_DR_ASYM(D_0047D4B0) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D4C0) "\n" RG_DR_ASYM(D_0047D4C0) " = " RG_DR_ASYM(D_0047D4B0) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D4C4) "\n" RG_DR_ASYM(D_0047D4C4) " = " RG_DR_ASYM(D_0047D4B0) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D4C8) "\n" RG_DR_ASYM(D_0047D4C8) " = " RG_DR_ASYM(D_0047D4B0) " + 0x18\n"
);
