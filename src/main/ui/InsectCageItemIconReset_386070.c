#include "types.h"

typedef unsigned __int128 u128;

struct T386070 { u8 pad000[0xC]; f32 f0C; s32 f10; };

void InsectCageItemIconReset_386070(struct T386070 *p)
{
    *(u128 *)p = 0;
    p->f0C = 1.0f;
    p->f10 = 0;
}
