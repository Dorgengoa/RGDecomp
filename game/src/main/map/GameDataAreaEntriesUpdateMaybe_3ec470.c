/* rgp:protos */
#define RGP_SELF_GameDataAreaEntriesUpdateMaybe_3ec470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct A3EC470 { u8 pad000[0x10]; void *f10; };
struct T3EC470 { u8 pad000[0x8]; void *f08; u8 pad00C[0xC]; struct A3EC470 *f18; };

/*rgp*/

s32 GameDataAreaEntriesUpdateMaybe_3ec470(struct T3EC470 *p, void *a, void *b)
{
    void *q;

    q = p->f08;
    if (q == 0) return 0;
    return WorldDataAreaEntriesUpdateMaybe_3f0cc0(q, p->f18->f10, a, b);
}
