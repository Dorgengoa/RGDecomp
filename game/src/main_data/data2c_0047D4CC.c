/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D4CC[7] __attribute__((section(".data$rg0047D4CC"))) = {
    @F@0047D4CC@, @F@0047D4D0@, @F@0047D4D4@, @F@0047D4D8@, @F@0047D4DC@, @F@0047D4E0@, @F@0047D4E4@
};
typedef char data2c_sizecheck_0047D4CC[(sizeof(D_0047D4CC) == 28) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D4D0) "\n" RG_DR_ASYM(D_0047D4D0) " = " RG_DR_ASYM(D_0047D4CC) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D4D4) "\n" RG_DR_ASYM(D_0047D4D4) " = " RG_DR_ASYM(D_0047D4CC) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D4D8) "\n" RG_DR_ASYM(D_0047D4D8) " = " RG_DR_ASYM(D_0047D4CC) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D4DC) "\n" RG_DR_ASYM(D_0047D4DC) " = " RG_DR_ASYM(D_0047D4CC) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D4E0) "\n" RG_DR_ASYM(D_0047D4E0) " = " RG_DR_ASYM(D_0047D4CC) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D4E4) "\n" RG_DR_ASYM(D_0047D4E4) " = " RG_DR_ASYM(D_0047D4CC) " + 0x18\n"
);
