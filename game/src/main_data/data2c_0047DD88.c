/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047DD88[30] __attribute__((section(".data$rg0047DD88"), aligned(8))) = {
    @F@0047DD88@, @F@0047DD8C@, @F@0047DD90@, @F@0047DD94@, @F@0047DD98@, @F@0047DD9C@, @F@0047DDA0@, @F@0047DDA4@, @F@0047DDA8@, @F@0047DDAC@, @F@0047DDB0@, @F@0047DDB4@, @F@0047DDB8@, @F@0047DDBC@, @F@0047DDC0@, @F@0047DDC4@, @F@0047DDC8@, @F@0047DDCC@, @F@0047DDD0@, @F@0047DDD4@, @F@0047DDD8@, @F@0047DDDC@, @F@0047DDE0@, @F@0047DDE4@, @F@0047DDE8@, @F@0047DDEC@, @F@0047DDF0@, @F@0047DDF4@, @F@0047DDF8@, @F@0047DDFC@
};
typedef char data2c_sizecheck_0047DD88[(sizeof(D_0047DD88) == 120) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047DD8C) "\n" RG_DR_ASYM(D_0047DD8C) " = " RG_DR_ASYM(D_0047DD88) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047DD90) "\n" RG_DR_ASYM(D_0047DD90) " = " RG_DR_ASYM(D_0047DD88) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047DD94) "\n" RG_DR_ASYM(D_0047DD94) " = " RG_DR_ASYM(D_0047DD88) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047DD98) "\n" RG_DR_ASYM(D_0047DD98) " = " RG_DR_ASYM(D_0047DD88) " + 0x10\n"
    ".globl " RG_DR_ASYM(D_0047DD9C) "\n" RG_DR_ASYM(D_0047DD9C) " = " RG_DR_ASYM(D_0047DD88) " + 0x14\n"
    ".globl " RG_DR_ASYM(D_0047DDA0) "\n" RG_DR_ASYM(D_0047DDA0) " = " RG_DR_ASYM(D_0047DD88) " + 0x18\n"
    ".globl " RG_DR_ASYM(D_0047DDA4) "\n" RG_DR_ASYM(D_0047DDA4) " = " RG_DR_ASYM(D_0047DD88) " + 0x1C\n"
    ".globl " RG_DR_ASYM(D_0047DDA8) "\n" RG_DR_ASYM(D_0047DDA8) " = " RG_DR_ASYM(D_0047DD88) " + 0x20\n"
    ".globl " RG_DR_ASYM(D_0047DDAC) "\n" RG_DR_ASYM(D_0047DDAC) " = " RG_DR_ASYM(D_0047DD88) " + 0x24\n"
    ".globl " RG_DR_ASYM(D_0047DDB0) "\n" RG_DR_ASYM(D_0047DDB0) " = " RG_DR_ASYM(D_0047DD88) " + 0x28\n"
    ".globl " RG_DR_ASYM(D_0047DDB4) "\n" RG_DR_ASYM(D_0047DDB4) " = " RG_DR_ASYM(D_0047DD88) " + 0x2C\n"
    ".globl " RG_DR_ASYM(D_0047DDB8) "\n" RG_DR_ASYM(D_0047DDB8) " = " RG_DR_ASYM(D_0047DD88) " + 0x30\n"
    ".globl " RG_DR_ASYM(D_0047DDBC) "\n" RG_DR_ASYM(D_0047DDBC) " = " RG_DR_ASYM(D_0047DD88) " + 0x34\n"
    ".globl " RG_DR_ASYM(D_0047DDC0) "\n" RG_DR_ASYM(D_0047DDC0) " = " RG_DR_ASYM(D_0047DD88) " + 0x38\n"
);
