/* rgp:protos */
#define RGP_SELF_GroupFindByKey_426e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E41E {
    u8    pad000[0x94];
    void *mFO;
    u8    padrest[0x98 - (0x94 + 4)];
} E41E;

typedef struct P41E {
    u8     pad000[0xC];
    E41E  *mO8;
} P41E;

extern s32 D_004644A8[];
/*rgp*/

E41E *GroupFindByKey_426e10(P41E *p, void *arg)
{
    E41E *e;
    s32 i;
    s32 n;

    e = p->mO8;
    if (e == 0) {
        return 0;
    }
    n = D_004644A8[0];
    for (i = 0; i < n; i++, e++) {
        if (e->mFO != 0) {
            if (GroupEntryMatchesKey_3f40e0(e->mFO, arg) != 0) {
                return e;
            }
        }
    }
    return 0;
}
