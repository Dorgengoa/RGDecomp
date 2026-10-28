/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D8F8[3] __attribute__((section(".data$rg0047D8F8"), aligned(8))) = {
    @F@0047D8F8@, @F@0047D8FC@, @F@0047D900@
};
typedef char data2c_sizecheck_0047D8F8[(sizeof(D_0047D8F8) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D900) "\n" RG_DR_ASYM(D_0047D900) " = " RG_DR_ASYM(D_0047D8F8) " + 0x8\n"
);
