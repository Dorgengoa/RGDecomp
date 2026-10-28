/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D808[4] __attribute__((section(".data$rg0047D808"), aligned(8))) = {
    @F@0047D808@, @F@0047D80C@, @F@0047D810@, @F@0047D814@
};
typedef char data2c_sizecheck_0047D808[(sizeof(D_0047D808) == 16) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D80C) "\n" RG_DR_ASYM(D_0047D80C) " = " RG_DR_ASYM(D_0047D808) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D810) "\n" RG_DR_ASYM(D_0047D810) " = " RG_DR_ASYM(D_0047D808) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D814) "\n" RG_DR_ASYM(D_0047D814) " = " RG_DR_ASYM(D_0047D808) " + 0xC\n"
);
