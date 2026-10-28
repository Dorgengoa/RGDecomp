/* rg-override: replaces game/src/main/gs/GsPktWriteAD_13ec80.c sha256 fc2c7226cd098e522d108c46cf64b9f02164443759c63951509d526de3163cd1
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* Packet builder: +0xF4 = write cursor (host pointer, 32-bit on i686).
   Each call writes one A+D qword: data u64 at +0, register id u64 at +8. */
void GsPktWriteAD_13ec80(void *pkt, s32 reg, u64 data)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u64 *)(p + 0x0) = data;
    *(s64 *)(p + 0x8) = (s64)reg; /* sd $5: the sign-extended register id */
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
