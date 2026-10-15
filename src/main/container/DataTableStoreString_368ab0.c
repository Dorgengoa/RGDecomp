#include "types.h"

struct T368AB0 { u8 pad000[0x7A]; u8 f7A_b0 : 1; u8 f7A_b1 : 1; u8 f7A_r : 6; };

extern s32 ArenaStrDup_3701d0(u8 *q, s32 a, s32 b, s32 c, s32 d);

s32 DataTableStoreString_368ab0(struct T368AB0 *p, s32 a)
{
    if (p->f7A_b1 != 0) return a;
    return ArenaStrDup_3701d0((u8 *)p + 0x6C, a, -1, 1, 1);
}
