/* rg-override: replaces game/src/main/gs/GsPktSetRGBAQ_13ee40.c sha256 014da7a32e81706fe35dbf8f8b0c10ff6ab64354dc8345cab864ae75add2709f
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* A+D write of RGBAQ (reg 1).  Each channel is sign-extended to 64 bits
   (dsll32/dsra32) before it is shifted and OR-ed, exactly as retail; Q is the
   float bit pattern kept at +0x110 (lwu, zero-extended) in bits 63:32. */
void GsPktSetRGBAQ_13ee40(void *pkt, s32 r, s32 g, s32 b, s32 a)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    u64 v = (u64)(s64)r
          | ((u64)(s64)g << 8)
          | ((u64)(s64)b << 16)
          | ((u64)(s64)a << 24);
    v |= (u64)*(u32 *)((u8 *)pkt + 0x110) << 32;
    *(u64 *)(p + 0x0) = v;
    *(u64 *)(p + 0x8) = 1;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
