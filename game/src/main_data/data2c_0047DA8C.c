/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DA8C[5] __attribute__((section(".data$rg0047DA8C"))) = {
    @F@0047DA8C@, @F@0047DA90@, @F@0047DA94@, @F@0047DA98@, @F@0047DA9C@
};
typedef char data2c_sizecheck_0047DA8C[(sizeof(D_0047DA8C) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DA90) "\n" RG_DR_ASYM(D_0047DA90) " = " RG_DR_ASYM(D_0047DA8C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DA98) "\n" RG_DR_ASYM(D_0047DA98) " = " RG_DR_ASYM(D_0047DA8C) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DA9C) "\n" RG_DR_ASYM(D_0047DA9C) " = " RG_DR_ASYM(D_0047DA8C) " + 0x10\n"
);
