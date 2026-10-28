/* rgp:protos */
#define RGP_SELF_TreasureBoxViewCount_426c90 1
#define RGP_SELF_get 1
#define RGP_SELF_get2 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_004644A8[0x100];

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x94 - 0x7E];
    s32 unk94;
} Ent;

typedef struct {
    u8 pad0[0xC];
    Ent *arr;
} Mgr;

typedef struct {
    u8 pad0[0x4];
    Mgr *mgr;
} Obj;



static inline Ent *get(Mgr *m, s32 i, s32 n)
{
    if (i >= 0 && i < n) {
        return &m->arr[i];
    }
    return NULL;
}

static inline Ent *get2(Mgr *m, s32 i, s32 n)
{
    if (i >= 0) {
        if (i >= n) {
            return NULL;
        }
        return &m->arr[i];
    }
    return NULL;
}

s32 TreasureBoxViewCount_426c90(Obj *arg0)
{
    s32 sum;
    s32 n;
    s32 i;
    Ent *e;
    Mgr *m;

    if (arg0->mgr == NULL) {
        return 0;
    }
    sum = 0;
    n = D_004644A8[0];
    for (i = 0; i < n; i++) {
        e = get2(arg0->mgr, i, n);
        if (e == NULL) {
            continue;
        }
        if (e->unk94 != 0 && GroupEntryMatchesKey_3f40e0(e->unk94, -1) != 0) {
            sum += e->unk7C;
        }
    }
    return sum;
}
