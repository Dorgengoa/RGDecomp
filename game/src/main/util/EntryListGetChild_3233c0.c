/* rgp:protos */
#define RGP_SELF_EntryListGetChild_3233c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3233C0 { u8 pad000[0x4]; u8 *f04; };

/*rgp*/

u8 *EntryListGetChild_3233c0(struct T3233C0 *p, s32 i)
{
    if (i < ((unsigned char)EntryListGetChildCount_323790(p))) {
        if (i >= 0) goto ok;
    }
    return 0;
ok:
    return p->f04 + i * 8;
}
