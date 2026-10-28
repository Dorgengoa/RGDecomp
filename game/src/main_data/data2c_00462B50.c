/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

s16 data2c_fragment_00462B50[1] __attribute__((section(".data$rg00462B50"), aligned(16))) = {
    @H@00462B50@
};
typedef char data2c_sizecheck_00462B50[(sizeof(data2c_fragment_00462B50) == 2) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_00462B50) "\n" RG_DR_ASYM(D_00462B50) " = " RG_DR_ASYM(data2c_fragment_00462B50) " + 0x0\n"
);
