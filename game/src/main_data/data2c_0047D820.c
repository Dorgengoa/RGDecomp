/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D820[3] __attribute__((section(".data$rg0047D820"), aligned(16))) = {
    @F@0047D820@, @F@0047D824@, @F@0047D828@
};
typedef char data2c_sizecheck_0047D820[(sizeof(D_0047D820) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D824) "\n" RG_DR_ASYM(D_0047D824) " = " RG_DR_ASYM(D_0047D820) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D828) "\n" RG_DR_ASYM(D_0047D828) " = " RG_DR_ASYM(D_0047D820) " + 0x8\n"
);
