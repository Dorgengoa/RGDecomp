/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D4E8[12] __attribute__((section(".data$rg0047D4E8"), aligned(8))) = {
    @F@0047D4E8@, @F@0047D4EC@, @F@0047D4F0@, @F@0047D4F4@, @F@0047D4F8@, @F@0047D4FC@, @F@0047D500@, @F@0047D504@, @F@0047D508@, @F@0047D50C@, @F@0047D510@, @F@0047D514@
};
typedef char data2c_sizecheck_0047D4E8[(sizeof(D_0047D4E8) == 48) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D4EC) "\n" RG_DR_ASYM(D_0047D4EC) " = " RG_DR_ASYM(D_0047D4E8) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D4F0) "\n" RG_DR_ASYM(D_0047D4F0) " = " RG_DR_ASYM(D_0047D4E8) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D4F4) "\n" RG_DR_ASYM(D_0047D4F4) " = " RG_DR_ASYM(D_0047D4E8) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D4F8) "\n" RG_DR_ASYM(D_0047D4F8) " = " RG_DR_ASYM(D_0047D4E8) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D4FC) "\n" RG_DR_ASYM(D_0047D4FC) " = " RG_DR_ASYM(D_0047D4E8) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D500) "\n" RG_DR_ASYM(D_0047D500) " = " RG_DR_ASYM(D_0047D4E8) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047D504) "\n" RG_DR_ASYM(D_0047D504) " = " RG_DR_ASYM(D_0047D4E8) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047D508) "\n" RG_DR_ASYM(D_0047D508) " = " RG_DR_ASYM(D_0047D4E8) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047D50C) "\n" RG_DR_ASYM(D_0047D50C) " = " RG_DR_ASYM(D_0047D4E8) " + 0x24\n"
    ".globl " RG_DR_ASYM(D_0047D510) "\n" RG_DR_ASYM(D_0047D510) " = " RG_DR_ASYM(D_0047D4E8) " + 0x28\n"
    ".globl " RG_DR_ASYM(D_0047D514) "\n" RG_DR_ASYM(D_0047D514) " = " RG_DR_ASYM(D_0047D4E8) " + 0x2C\n"
);
