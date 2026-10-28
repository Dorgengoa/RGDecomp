/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

s16 data2c_fragment_0044B778[1] __attribute__((section(".data$rg0044B778"), aligned(8))) = {
    @H@0044B778@
};
typedef char data2c_sizecheck_0044B778[(sizeof(data2c_fragment_0044B778) == 2) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0044B778) "\n" RG_DR_ASYM(D_0044B778) " = " RG_DR_ASYM(data2c_fragment_0044B778) " + 0x0\n"
);
