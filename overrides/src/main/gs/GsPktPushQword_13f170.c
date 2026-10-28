/* rg-override: replaces game/src/main/gs/GsPktPushQword_13f170.c sha256 353934d7fb1db1a5b4778a9b3de377878f8b9c54cea46cbaaa8b2d1ced5ca1c8
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* lq $6, 0($5) / sq $6, 0(cursor): copy one qword into the packet. */
void GsPktPushQword_13f170(void *pkt, const void *src)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u8 **)((u8 *)pkt + 0xF4) = p + 0x10;
    __builtin_memcpy(p, src, 16);
}
