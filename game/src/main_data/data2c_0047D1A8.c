/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

u32 D_0047D1A8[6] __attribute__((section(".data$rg0047D1A8"), aligned(8))) = {
    @X@0047D1A8@, @X@0047D1AC@, @X@0047D1B0@, @X@0047D1B4@, @X@0047D1B8@, @X@0047D1BC@
};
typedef char data2c_sizecheck_0047D1A8[(sizeof(D_0047D1A8) == 24) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D1B0) "\n" RG_DR_ASYM(D_0047D1B0) " = " RG_DR_ASYM(D_0047D1A8) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D1B8) "\n" RG_DR_ASYM(D_0047D1B8) " = " RG_DR_ASYM(D_0047D1A8) " + 0x10\n"
);
