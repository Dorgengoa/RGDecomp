/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DD2C[3] __attribute__((section(".data$rg0047DD2C"))) = {
    @F@0047DD2C@, @F@0047DD30@, @F@0047DD34@
};
typedef char data2c_sizecheck_0047DD2C[(sizeof(D_0047DD2C) == 12) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DD30) "\n" RG_DR_ASYM(D_0047DD30) " = " RG_DR_ASYM(D_0047DD2C) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DD34) "\n" RG_DR_ASYM(D_0047DD34) " = " RG_DR_ASYM(D_0047DD2C) " + 0x8\n"
);
