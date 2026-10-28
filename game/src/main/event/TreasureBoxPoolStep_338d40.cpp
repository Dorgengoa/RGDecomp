/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"

struct Elem {
    u8 pad0[0x40];
    s32 flags;      /* +0x40 */
};

struct Item {
    u8 pad0[0x68];
    s32 link;       /* +0x68 */
    u8 pad6c[0x4];
    bool b0 : 1;    /* +0x70 */
    bool b1 : 1;
    u8 pad71[0xF];
};

struct Obj {
    Item *items;    /* +0x00 */
    Item **arr;     /* +0x04 */
    s16 count;      /* +0x08 */
    bool c0 : 1;    /* +0x0A */
    bool c1 : 1;
};

struct Actor {
    u8 pad0[0x18];
    u8 *info;       /* +0x18 */
};

extern "C" {
s32 GetActionMgr_1fdb50();
Actor *GetGameData_1fede0();
s32 ActionMgrFindById_233b50(s32, s16);
void CharaGetPos_2388a0(s32, u8 *);
void TreasureBoxUpdate_3398c0(Item *);
s32 TreasureBoxIsAnimating_33ae10(Item *);
float TreasureBoxUpdateDist_33ae40(Item *, u8 *);
s32 TreasureBoxGetSortKey_33b140(Item *);
Elem *TreasureBoxResolveRec_33b180(Item *);
void TreasureBoxPlaceFromMapRec_33b1e0(Item *, Elem *);
void TreasureBoxReset_33b4c0(Item *);
Elem *IterNext_370040(void *);
void IterReset_3700f0(void *);
void IterInit_370170(void *, void *, int, int);
void TreasureBoxViewCtor_426d70(void *, Actor *, s32);
}

extern "C" s32 TreasureBoxPoolStep_338d40(Obj *arg0)
{
    struct { u32 hd[2]; u32 it[2]; u32 list[4]; } ctx;
    u8 buf[16] __attribute__((aligned(16)));
    Item *item;
    s32 first;
    s32 i;
    bool swapped;
    Item **pp;
    s32 h;
    Actor *actor;
    s32 h2;
    bool ok;
    s32 v;
    Elem *e;
    bool end;

    if (arg0->items == 0) {
        return 0;
    }
    if (arg0->arr == 0) {
        return 0;
    }
    actor = GetGameData_1fede0();
    if (actor == 0) {
        return 0;
    }
    h = GetActionMgr_1fdb50();
    if (h == 0) {
        return 0;
    }
    { u8 *p_ = buf; u32 n_ = 16; if (p_ != 0) { do { *p_ = 0; n_--; p_++; } while (n_ != 0); } }
    h2 = ActionMgrFindById_233b50(h, *(s16 *)(actor->info + 0x18E));
    if (h2 != 0) {
        CharaGetPos_2388a0(h2, buf);
    }
    TreasureBoxViewCtor_426d70(ctx.list, actor, -1);
    IterInit_370170(ctx.it, ctx.list, 0, 0);
    while ((e = IterNext_370040(ctx.it)) != 0) {
        e->flags &= ~1;
    }

    item = arg0->items;
    first = -1;
    i = 0;
    do {
        ok = true;
        e = TreasureBoxResolveRec_33b180(item);
        if (e != 0 && (e->flags & 2)) {
            TreasureBoxUpdateDist_33ae40(item, buf);
            if (item->b0 || ((unsigned char)TreasureBoxIsAnimating_33ae10(item)) != 0) {
                ok = false;
                e->flags |= 1;
            }
        }
        if (ok) {
            TreasureBoxReset_33b4c0(item);
            if (first < 0) {
                first = i;
            }
        }
        i++;
        item++;
    } while (i < 32);

    item = &arg0->items[first];
    IterReset_3700f0(ctx.it);
    while (!(end = (e = IterNext_370040(ctx.it), e != 0) ^ 1) && first < 32) {
        if (!(e->flags & 1) && (e->flags & 2)) {
            TreasureBoxPlaceFromMapRec_33b1e0(item, e);
            TreasureBoxUpdateDist_33ae40(item, buf);
            if (item->b0 || ((unsigned char)TreasureBoxIsAnimating_33ae10(item)) != 0) {
                first++;
                e->flags |= 1;
                for (; first < 32; first++) {
                    if (item->link == 0) break;
                }
            }
        }
    }

    arg0->count = 0;
    {
        s32 i3;
    pp = arg0->arr;
    item = arg0->items;
    for (i3 = 0; i3 < 32; i3++, item++) {
        if (item->b0 || ((unsigned char)TreasureBoxIsAnimating_33ae10(item)) != 0) {
            *pp = item;
            pp++;
            if (++arg0->count >= 32) {
                break;
            }
        }
    }
    }

    if (arg0->count <= 0) {
        return 0;
    }
    do {
        Item **p4;
        Item **q;
        s32 i4;
        p4 = arg0->arr;
        swapped = false;
        for (i4 = 1, q = p4 + 1; i4 < arg0->count; i4++, q++) {
            bool less;
            less = false;
            v = TreasureBoxGetSortKey_33b140(*p4);
            if (TreasureBoxGetSortKey_33b140(*q) < v) {
                less = true;
            }
            if (less) {
                Item *t = *p4;
                swapped = true;
                *p4 = *q;
                *q = t;
            } else {
                p4 = q;
            }
        }
    } while (swapped);

    arg0->c1 = false;
    pp = arg0->arr;
    for (i = 0; i < arg0->count; i++, pp++) {
        item = *pp;
        if (item != 0) {
            TreasureBoxUpdate_3398c0(item);
            if (item->b1) {
                arg0->c1 = true;
            }
        }
    }
    return 0;
}
