/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00468750[];
u32 D_004802C4[3] __attribute__((section(".data$rg004802C4"))) = {
    (u32)((u8*)&D_00468750 + 0x340u), (u32)((u8*)&D_00468750 + 0x360u), (u32)((u8*)&D_00468750 + 0x380u)
};
typedef char data2c_sizecheck_004802C4[(sizeof(D_004802C4) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_004802CC) "\n" RG_DR_ASYM(D_004802CC) " = " RG_DR_ASYM(D_004802C4) " + 0x8\n"
);
