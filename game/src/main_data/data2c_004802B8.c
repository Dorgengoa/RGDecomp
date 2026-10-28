/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00468750[];
u32 D_004802B8[3] __attribute__((section(".data$rg004802B8"), aligned(8))) = {
    (u32)((u8*)&D_00468750 + 0x2D0u), (u32)((u8*)&D_00468750 + 0x300u), (u32)((u8*)&D_00468750 + 0x320u)
};
typedef char data2c_sizecheck_004802B8[(sizeof(D_004802B8) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_004802BC) "\n" RG_DR_ASYM(D_004802BC) " = " RG_DR_ASYM(D_004802B8) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_004802C0) "\n" RG_DR_ASYM(D_004802C0) " = " RG_DR_ASYM(D_004802B8) " + 0x8\n"
);
