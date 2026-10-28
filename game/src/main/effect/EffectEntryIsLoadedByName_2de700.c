/* rgp:protos */
#define RGP_SELF_EffectEntryIsLoadedByName_2de700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffectEntryIsLoadedByName_2de700(int rgp_a0, int rgp_a1)
{
    u8 *r;
    u8 *q;

    r = ((u8 *)EffectFindByNameNoId_2dfed0((int)rgp_a0, (int)rgp_a1));
    if (r != 0) goto g1;
    return 0;
g1:
    q = r + 0xC;
    if (q != 0) {
        if (*(s16 *)(q + 0xA) != 1) return 0;
        return *(s16 *)(q + 0xC) == 1;
    }
    return 0;
}
