/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D53C[10] __attribute__((section(".data$rg0047D53C"))) = {
    @F@0047D53C@, @F@0047D540@, @F@0047D544@, @F@0047D548@, @F@0047D54C@, @F@0047D550@, @F@0047D554@, @F@0047D558@, @F@0047D55C@, @F@0047D560@
};
typedef char data2c_sizecheck_0047D53C[(sizeof(D_0047D53C) == 40) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D540) "\n" RG_DR_ASYM(D_0047D540) " = " RG_DR_ASYM(D_0047D53C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D544) "\n" RG_DR_ASYM(D_0047D544) " = " RG_DR_ASYM(D_0047D53C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D548) "\n" RG_DR_ASYM(D_0047D548) " = " RG_DR_ASYM(D_0047D53C) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D54C) "\n" RG_DR_ASYM(D_0047D54C) " = " RG_DR_ASYM(D_0047D53C) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D550) "\n" RG_DR_ASYM(D_0047D550) " = " RG_DR_ASYM(D_0047D53C) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D554) "\n" RG_DR_ASYM(D_0047D554) " = " RG_DR_ASYM(D_0047D53C) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047D558) "\n" RG_DR_ASYM(D_0047D558) " = " RG_DR_ASYM(D_0047D53C) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047D55C) "\n" RG_DR_ASYM(D_0047D55C) " = " RG_DR_ASYM(D_0047D53C) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047D560) "\n" RG_DR_ASYM(D_0047D560) " = " RG_DR_ASYM(D_0047D53C) " + 0x24\n"
);
