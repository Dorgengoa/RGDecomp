/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D564[5] __attribute__((section(".data$rg0047D564"))) = {
    @F@0047D564@, @F@0047D568@, @F@0047D56C@, @F@0047D570@, @F@0047D574@
};
typedef char data2c_sizecheck_0047D564[(sizeof(D_0047D564) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D568) "\n" RG_DR_ASYM(D_0047D568) " = " RG_DR_ASYM(D_0047D564) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D56C) "\n" RG_DR_ASYM(D_0047D56C) " = " RG_DR_ASYM(D_0047D564) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D570) "\n" RG_DR_ASYM(D_0047D570) " = " RG_DR_ASYM(D_0047D564) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D574) "\n" RG_DR_ASYM(D_0047D574) " = " RG_DR_ASYM(D_0047D564) " + 0x10\n"
);
