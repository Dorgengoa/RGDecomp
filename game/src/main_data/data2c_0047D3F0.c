/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D3F0[2] __attribute__((section(".data$rg0047D3F0"), aligned(16))) = {
    @F@0047D3F0@, @F@0047D3F4@
};
typedef char data2c_sizecheck_0047D3F0[(sizeof(D_0047D3F0) == 8) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D3F4) "\n" RG_DR_ASYM(D_0047D3F4) " = " RG_DR_ASYM(D_0047D3F0) " + 0x4\n"
);
