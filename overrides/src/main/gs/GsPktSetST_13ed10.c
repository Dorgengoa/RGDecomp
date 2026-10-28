/* rg-override: replaces game/src/main/gs/GsPktSetST_13ed10.c sha256 c179558f16a91d040620e159103e030de4279dbe3e92a1f7653e6dc243728621
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* ST (reg 2): S bits in 31:0, T bits in 63:32; Q is stored at +0x110 for the
   next RGBAQ. */
void GsPktSetST_13ed10(void *pkt, f32 s, f32 t, f32 q)
{
    u32 sb, tb;
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    __builtin_memcpy(&sb, &s, 4);
    __builtin_memcpy(&tb, &t, 4);
    *(f32 *)((u8 *)pkt + 0x110) = q;
    *(u64 *)(p + 0x0) = (u64)sb | ((u64)tb << 32);
    *(u64 *)(p + 0x8) = 2;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
