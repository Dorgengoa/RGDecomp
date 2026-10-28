/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DA74[6] __attribute__((section(".data$rg0047DA74"))) = {
    @F@0047DA74@, @F@0047DA78@, @F@0047DA7C@, @F@0047DA80@, @F@0047DA84@, @F@0047DA88@
};
typedef char data2c_sizecheck_0047DA74[(sizeof(D_0047DA74) == 24) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DA78) "\n" RG_DR_ASYM(D_0047DA78) " = " RG_DR_ASYM(D_0047DA74) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DA80) "\n" RG_DR_ASYM(D_0047DA80) " = " RG_DR_ASYM(D_0047DA74) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DA84) "\n" RG_DR_ASYM(D_0047DA84) " = " RG_DR_ASYM(D_0047DA74) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DA88) "\n" RG_DR_ASYM(D_0047DA88) " = " RG_DR_ASYM(D_0047DA74) " + 0x14\n"
);
