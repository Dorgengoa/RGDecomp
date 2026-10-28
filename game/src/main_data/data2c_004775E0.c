/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
u32 D_004775E0[16] __attribute__((section(".data$rg004775E0"), aligned(16))) = {
    @X@004775E0@, @X@004775E4@, (u32)&ContainerViewCountNop_370160, (u32)&ContainerViewGetAtFwd_3fcb80, (u32)&func_003FCB80_e1, @X@004775F4@, @X@004775F8@, @X@004775FC@, @X@00477600@, @X@00477604@, (u32)&HunterBountyIterGetCount_3fcd80, (u32)&ContainerViewGetAtFwd_3fe230, (u32)&HunterBountyIterGetAt_3fcd90, @X@00477614@, @X@00477618@, @X@0047761C@
};
typedef char data2c_sizecheck_004775E0[(sizeof(D_004775E0) == 64) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_00477600) "\n" RG_DR_ASYM(D_00477600) " = " RG_DR_ASYM(D_004775E0) " + 0x20\n"
);
