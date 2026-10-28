/* rgp:protos */
#define RGP_SELF_CharaSysStateRuleLookupRelated_3a3710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3a3710 { u8 pad000[0x8]; s16 m08; u8 pad00A[0x2]; s16 m0C; };
struct G3a3710 { u8 pad000[0x70]; s32 m70; };
struct A3a3710 { u8 pad000[0x238]; struct T3a3710 *m238; };

extern struct G3a3710 *D_004837C4;
/*rgp*/

s32 CharaSysStateRuleLookupRelated_3a3710(struct A3a3710 *a)
{
    struct G3a3710 *g;
    struct T3a3710 *t;

    g = D_004837C4;
    if (g == 0) {
        return 0;
    }
    t = a->m238;
    if (t == 0) {
        return 0;
    }
    return GroupGetRecordById_402240(g->m70, (long long)(t->m08), (long long)(t->m0C));
}
