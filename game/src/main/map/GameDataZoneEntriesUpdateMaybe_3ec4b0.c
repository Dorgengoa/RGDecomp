/* rgp:protos */
#define RGP_SELF_GameDataZoneEntriesUpdateMaybe_3ec4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct A3EC4B0 { u8 pad000[0xC]; s16 f0C; };
struct T3EC4B0 { u8 pad000[0x8]; void *f08; u8 pad00C[0xC]; struct A3EC4B0 *f18; };

/*rgp*/

s32 GameDataZoneEntriesUpdateMaybe_3ec4b0(struct T3EC4B0 *p, void *a, void *b)
{
    void *q;

    q = p->f08;
    if (q == 0) return 0;
    return WorldDataZoneEntriesUpdateMaybe_3f1660(q, p->f18->f0C, a, b);
}
