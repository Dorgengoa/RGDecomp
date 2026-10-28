/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D920[4] __attribute__((section(".data$rg0047D920"), aligned(16))) = {
    @F@0047D920@, @F@0047D924@, @F@0047D928@, @F@0047D92C@
};
typedef char data2c_sizecheck_0047D920[(sizeof(D_0047D920) == 16) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D924) "\n" RG_DR_ASYM(D_0047D924) " = " RG_DR_ASYM(D_0047D920) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D928) "\n" RG_DR_ASYM(D_0047D928) " = " RG_DR_ASYM(D_0047D920) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D92C) "\n" RG_DR_ASYM(D_0047D92C) " = " RG_DR_ASYM(D_0047D920) " + 0xC\n"
);
