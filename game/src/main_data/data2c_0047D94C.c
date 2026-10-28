/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D94C[5] __attribute__((section(".data$rg0047D94C"))) = {
    @F@0047D94C@, @F@0047D950@, @F@0047D954@, @F@0047D958@, @F@0047D95C@
};
typedef char data2c_sizecheck_0047D94C[(sizeof(D_0047D94C) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D950) "\n" RG_DR_ASYM(D_0047D950) " = " RG_DR_ASYM(D_0047D94C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D954) "\n" RG_DR_ASYM(D_0047D954) " = " RG_DR_ASYM(D_0047D94C) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D958) "\n" RG_DR_ASYM(D_0047D958) " = " RG_DR_ASYM(D_0047D94C) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D95C) "\n" RG_DR_ASYM(D_0047D95C) " = " RG_DR_ASYM(D_0047D94C) " + 0x10\n"
);
