/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00468750[];
u32 D_004802A0[5] __attribute__((section(".data$rg004802A0"), aligned(16))) = {
    (u32)((u8*)&D_00468750 + 0x200u), (u32)((u8*)&D_00468750 + 0x230u), (u32)((u8*)&D_00468750 + 0x250u), (u32)((u8*)&D_00468750 + 0x270u), (u32)((u8*)&D_00468750 + 0x290u)
};
typedef char data2c_sizecheck_004802A0[(sizeof(D_004802A0) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_004802A4) "\n" RG_DR_ASYM(D_004802A4) " = " RG_DR_ASYM(D_004802A0) " + 0x4\n"
);
