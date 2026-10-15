#include "types.h"

struct T3233C0 { u8 pad000[0x4]; u8 *f04; };

extern s32 EntryListGetChildCount_323790(struct T3233C0 *p);

u8 *EntryListGetChild_3233c0(struct T3233C0 *p, s32 i)
{
    if (i < EntryListGetChildCount_323790(p)) {
        if (i >= 0) goto ok;
    }
    return 0;
ok:
    return p->f04 + i * 8;
}
