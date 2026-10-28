/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DD44[15] __attribute__((section(".data$rg0047DD44"))) = {
    @F@0047DD44@, @F@0047DD48@, @F@0047DD4C@, @F@0047DD50@, @F@0047DD54@, @F@0047DD58@, @F@0047DD5C@, @F@0047DD60@, @F@0047DD64@, @F@0047DD68@, @F@0047DD6C@, @F@0047DD70@, @F@0047DD74@, @F@0047DD78@, @F@0047DD7C@
};
typedef char data2c_sizecheck_0047DD44[(sizeof(D_0047DD44) == 60) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DD48) "\n" RG_DR_ASYM(D_0047DD48) " = " RG_DR_ASYM(D_0047DD44) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DD4C) "\n" RG_DR_ASYM(D_0047DD4C) " = " RG_DR_ASYM(D_0047DD44) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DD50) "\n" RG_DR_ASYM(D_0047DD50) " = " RG_DR_ASYM(D_0047DD44) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DD54) "\n" RG_DR_ASYM(D_0047DD54) " = " RG_DR_ASYM(D_0047DD44) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DD58) "\n" RG_DR_ASYM(D_0047DD58) " = " RG_DR_ASYM(D_0047DD44) " + 0x14\n"
);
