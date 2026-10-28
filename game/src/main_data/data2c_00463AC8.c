/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

s16 data2c_fragment_00463AC8[1] __attribute__((section(".data$rg00463AC8"), aligned(8))) = {
    @H@00463AC8@
};
typedef char data2c_sizecheck_00463AC8[(sizeof(data2c_fragment_00463AC8) == 2) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_00463AC8) "\n" RG_DR_ASYM(D_00463AC8) " = " RG_DR_ASYM(data2c_fragment_00463AC8) " + 0x0\n"
);
