/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DA6C[2] __attribute__((section(".data$rg0047DA6C"))) = {
    @F@0047DA6C@, @F@0047DA70@
};
typedef char data2c_sizecheck_0047DA6C[(sizeof(D_0047DA6C) == 8) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DA70) "\n" RG_DR_ASYM(D_0047DA70) " = " RG_DR_ASYM(D_0047DA6C) " + 0x4\n"
);
