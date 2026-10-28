/* rgp:protos */
#define RGP_SELF_factory_FactoryMergeInputsMatchType3Maybe_4f4a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma optimization_level 3

typedef struct Item {
    s16 f00;
} Item;

typedef struct Slot {
    Item *f00;
    u8    pad04[0xC];
} Slot;                                         /* 0x10 */

typedef struct List {
    u8    pad00[0xC];
    Slot *f0C;
} List;

typedef struct Ctx {
    u8    pad00[0x70];
    List *f70;
} Ctx;

typedef struct Ent {
    u8  pad00[0x4];
    s16 f04;
    u8  pad06[0x2A];
    s16 f30;
    u8  pad32[0xE];
} Ent;                                          /* 0x40 */

typedef struct World {
    u8  pad000[0xE0];
    Ent f0E0[1];
} World;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

/*rgp*/
extern void   memset(void *p, s32 v, s32 n);

u8 factory_FactoryMergeInputsMatchType3Maybe_4f4a10(void *unused, s32 n, s32 *ids)
{
    List  *lst;
    World *w;
    Ent   *ents;
    Ent   *e;
    Slot  *slots;
    Slot  *a;
    Slot  *b;
    s32    va[2];
    s32    vb[2];
    s32    vc[2];
    u8     ok;
    u8     bad;
    s32    i;
    s32    j;
    s32    cnt;
    u8     r;

    if (D_00484A48 == 0) {
        return 0;
    }
    lst = D_00484A48->f70;
    if (lst == 0) {
        return 0;
    }
    w = ((World *)GetFactoryObj_367f30());
    if (w == 0) {
        return 0;
    }
    ents = w->f0E0;
    ok = 1;
    bad = 0;
    for (i = 0; i < n && ok; i++) {
        if (ents[ids[i]].f30 == 8) {
            ok = 0;
            bad = 1;
        }
    }
    memset(va, -1, 8);
    memset(va, -1, 8);
    memset(va, -1, 8);
    slots = lst->f0C;
    if (!bad) {
        for (j = 0; j < 2; j++) {
            e = &ents[ids[j]];
            if (e == 0) {
                continue;
            }
            a = &slots[j];
            if (a == 0) {
                continue;
            }
            b = a + 2;
            if (b == 0) {
                continue;
            }
            va[j] = e->f04;
            vb[j] = a->f00->f00;
            vc[j] = b->f00->f00;
        }
    }
    r = 0;
    if (bad) {
        r = 1;
    } else {
    cnt = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (vb[i] == va[j]) {
                cnt++;
            }
        }
    }
    if (cnt == 0) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                if (vc[i] == va[j]) {
                    cnt++;
                }
            }
        }
        if (cnt == 2) {
            r = 1;
        }
    } else {
        if (cnt == 2) {
            r = 1;
        }
    }
    }
    return r;
}
