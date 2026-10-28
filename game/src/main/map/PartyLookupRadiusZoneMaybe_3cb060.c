/* rgp:protos */
#define RGP_SELF_PartyLookupRadiusZoneMaybe_3cb060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E {
    u8 pad000[0x5E];
    s16 a;
    s16 b;
};

struct G {
    u8 pad00[0x34];
    void *m34;
};

extern struct G *D_00483894 __attribute__((section(".sdata")));
/*rgp*/

s32 PartyLookupRadiusZoneMaybe_3cb060(void *o, s32 i)
{
    struct G *g;
    struct E *e;

    if (i < 0 || i >= 8) {
        return 0;
    }
    g = D_00483894;
    if (g == 0) {
        return 0;
    }
    e = (struct E *)((u8 *)o + i * 4);
    return ((s32)GroupRangeLookup_411500(g->m34, e->a, e->b));
}
