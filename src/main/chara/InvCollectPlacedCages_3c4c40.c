#include "types.h"

typedef struct {
    u8 pad0[6];
    s16 lv;
    u8 pad8[2];
    u8 b0 : 1;
    u8 dis : 1;
} Ent;

typedef struct {
    u8 pad0[6];
    s16 id;
} Kind;

typedef struct {
    u8 pad0[0x18];
    Kind *kind;
} Unit;

typedef struct {
    u8 pad0[0x168];
    s32 x168;
} Obj;

extern Ent *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 CageRecIsPlaced_3d0d20(Unit *arg0);
extern Unit *InvObjCastToItem4B0_3d3cd0(Ent *arg0);
extern s32 D_00465A08[4];
extern s32 D_00465A10[4];
extern s32 D_00465B50[4];

s32 InvCollectPlacedCages_3c4c40(Obj *self, s32 kind, Unit **arr, s32 max)
{
    s32 count;
    s32 lo;
    s32 hi;
    s32 n;
    s32 i;
    Ent *e;
    Unit *u;

    if (arr == NULL) {
        return 0;
    }
    if (max <= 0) {
        return 0;
    }
    count = 0;
    lo = D_00465A08[0];
    hi = D_00465A10[0];
    for (i = 0, n = D_00465B50[0]; i < n; i++) {
        e = PoolGetUsedElem_36acb0(self->x168, i);
        if (e == NULL) {
            continue;
        }
        if (e->dis) {
            continue;
        }
        if (e->lv < lo) {
            continue;
        }
        if (e->lv > hi) {
            continue;
        }
        u = InvObjCastToItem4B0_3d3cd0(e);
        if (u == NULL) {
            continue;
        }
        if (CageRecIsPlaced_3d0d20(u) == 0) {
            continue;
        }
        if (kind != u->kind->id) {
            continue;
        }
        arr[count++] = u;
        if (count >= max) {
            break;
        }
    }
    return count;
}
