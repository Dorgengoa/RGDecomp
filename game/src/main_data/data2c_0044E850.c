/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

u8 data2c_fragment_0044E850[1] __attribute__((section(".data$rg0044E850"), aligned(16))) = {
    @B@0044E850@
};
typedef char data2c_sizecheck_0044E850[(sizeof(data2c_fragment_0044E850) == 1) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0044E850) "\n" RG_DR_ASYM(D_0044E850) " = " RG_DR_ASYM(data2c_fragment_0044E850) " + 0x0\n"
);
