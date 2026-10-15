#include "types.h"

#pragma opt_common_subs off

struct T102690 { u8 pad000[0xC]; const void *f0C; const void *f10; };

extern const u8 D_0047D130[];

s32 EhFindExceptionTableMaybe_102690(struct T102690 *p)
{
    p->f0C = (const void *)D_0047D130;
    p->f10 = (const void *)D_0047D130;
    return 1;
}
