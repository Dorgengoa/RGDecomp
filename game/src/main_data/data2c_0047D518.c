/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D518[9] __attribute__((section(".data$rg0047D518"), aligned(8))) = {
    @F@0047D518@, @F@0047D51C@, @F@0047D520@, @F@0047D524@, @F@0047D528@, @F@0047D52C@, @F@0047D530@, @F@0047D534@, @F@0047D538@
};
typedef char data2c_sizecheck_0047D518[(sizeof(D_0047D518) == 36) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D51C) "\n" RG_DR_ASYM(D_0047D51C) " = " RG_DR_ASYM(D_0047D518) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D520) "\n" RG_DR_ASYM(D_0047D520) " = " RG_DR_ASYM(D_0047D518) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D524) "\n" RG_DR_ASYM(D_0047D524) " = " RG_DR_ASYM(D_0047D518) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D528) "\n" RG_DR_ASYM(D_0047D528) " = " RG_DR_ASYM(D_0047D518) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047D52C) "\n" RG_DR_ASYM(D_0047D52C) " = " RG_DR_ASYM(D_0047D518) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047D534) "\n" RG_DR_ASYM(D_0047D534) " = " RG_DR_ASYM(D_0047D518) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047D538) "\n" RG_DR_ASYM(D_0047D538) " = " RG_DR_ASYM(D_0047D518) " + 0x20\n"
);
