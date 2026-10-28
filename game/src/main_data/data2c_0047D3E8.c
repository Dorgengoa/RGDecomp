/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D3E8[2] __attribute__((section(".data$rg0047D3E8"), aligned(8))) = {
    @F@0047D3E8@, @F@0047D3EC@
};
typedef char data2c_sizecheck_0047D3E8[(sizeof(D_0047D3E8) == 8) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D3EC) "\n" RG_DR_ASYM(D_0047D3EC) " = " RG_DR_ASYM(D_0047D3E8) " + 0x4\n"
);
