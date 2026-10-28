/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

f32 D_0047D3D0[5] __attribute__((section(".data$rg0047D3D0"), aligned(16))) = {
    @F@0047D3D0@, @F@0047D3D4@, @F@0047D3D8@, @F@0047D3DC@, @F@0047D3E0@
};
typedef char data2c_sizecheck_0047D3D0[(sizeof(D_0047D3D0) == 20) ? 1 : -1];

/* interior names (datareloc stage, docs/LINK.md) */
#if defined(_WIN32) && defined(__i386__)
#define RG_DR_ASYM(s) "_" #s
#else
#define RG_DR_ASYM(s) #s
#endif
__asm__(
    ".globl " RG_DR_ASYM(D_0047D3D4) "\n" RG_DR_ASYM(D_0047D3D4) " = " RG_DR_ASYM(D_0047D3D0) " + 0x4\n"
    ".globl " RG_DR_ASYM(D_0047D3D8) "\n" RG_DR_ASYM(D_0047D3D8) " = " RG_DR_ASYM(D_0047D3D0) " + 0x8\n"
    ".globl " RG_DR_ASYM(D_0047D3DC) "\n" RG_DR_ASYM(D_0047D3DC) " = " RG_DR_ASYM(D_0047D3D0) " + 0xC\n"
    ".globl " RG_DR_ASYM(D_0047D3E0) "\n" RG_DR_ASYM(D_0047D3E0) " = " RG_DR_ASYM(D_0047D3D0) " + 0x10\n"
);
