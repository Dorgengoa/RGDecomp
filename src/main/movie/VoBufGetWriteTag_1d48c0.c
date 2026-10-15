#include "types.h"
#pragma divbyzerocheck on
struct S1d48c0 { u8 pad000[0x8]; s32 m08; s32 m0C; u8 pad010[0x4]; s32 m14; };

s32 VoBufGetWriteTag_1d48c0(struct S1d48c0 *p)
{
    return p->m08 + ((p->m0C + p->m14) % p->m14) * 0x48;
}
