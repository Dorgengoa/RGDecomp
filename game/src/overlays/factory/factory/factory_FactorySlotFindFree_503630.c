/* rgp:protos */
#define RGP_SELF_factory_FactorySlotFindFree_503630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 pad00[0x4]; s16 f04; u8 pad06[0x3A]; } Ent;
typedef struct S { u8 pad00[0xE0]; Ent e[4]; } S;

Ent *factory_FactorySlotFindFree_503630(S *p)
{
    Ent *e;
    s32  i;

    e = p->e;
    for (i = 0; i < 4; i++, e++) {
        if (e->f04 < 0) {
            return e;
        }
    }
    return 0;
}
