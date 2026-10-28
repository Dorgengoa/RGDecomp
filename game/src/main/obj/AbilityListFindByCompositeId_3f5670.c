/* rgp:protos */
#define RGP_SELF_AbilityListFindByCompositeId_3f5670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct IdObj {
    u8 pad0[5];
    u8 unk5;
} IdObj;

typedef struct Entry3f5670 {
    u8 pad0[4];
    IdObj *unk4;
    u8 pad8[4];
} Entry3f5670;

typedef struct T3f5670 {
    u8 pad0[8];
    s32 unk8;
    Entry3f5670 *unkC;
} T3f5670;

/*rgp*/

void *AbilityListFindByCompositeId_3f5670(T3f5670 *arg0, s32 arg1, s32 arg2)
{
    Entry3f5670 *cur;
    s32 i;
    IdObj *id;

    cur = arg0->unkC;
    if (cur == NULL || arg0->unk8 <= 0) {
        return NULL;
    }
    for (i = 0; i < arg0->unk8; i += 1, cur += 1) {
        id = cur->unk4;
        if (id != NULL && arg1 == AbilityDataGetCompositeId_3f5e10(id) && cur->unk4->unk5 == arg2) {
            return cur;
        }
    }
    return NULL;
}
