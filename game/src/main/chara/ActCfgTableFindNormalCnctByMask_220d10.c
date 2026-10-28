/* rgp:protos */
#define RGP_SELF_ActCfgTableFindNormalCnctByMask_220d10 1
#define RGP_SELF_Find 1
#define RGP_SELF_Lookup 1
#define RGP_SELF_Try1 1
#define RGP_SELF_Try2 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    char *name;
    s32 x4;
    u8 pad8[0x20 - 8];
    u8 *x20;
    s16 x24;
    u8 pad26[0x32 - 0x26];
    s16 x32;
} Ent;

typedef struct Grp {
    u8 pad0[0x1C];
    u8 *x1C;
    u8 pad20[4];
    s16 x24;
    u8 pad26[2];
    Ent *x28;
    s16 x2C;
} Grp;

typedef struct Node {
    u8 pad0[0x10];
    Grp grp;
} Node;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Node *Lookup(u8 *tree, s32 key) {
    Node *cur;
    Node *res;
    s32 step;
    Node *n;
    s32 c;
    if ((cur = ((Node *)DListGetHead_42ea60(tree))) == 0) {
        res = 0;
    } else {
        res = 0;
        step = ((unsigned short)DListGetCountPow2_42ea70(tree));
        while (step > 0) {
            step >>= 1;
            n = ((Node *)DListNodeAdvance_42eb00(cur, step));
            if (n != 0) {
                c = IntCompare_42ca30(key, *(s16 *)((u8 *)n + 0x3E));
                if (c == 0) {
                    res = n;
                    break;
                }
                if (c > 0) {
                    cur = n;
                }
            }
        }
    }
    return res;
}

static inline Ent *Find(Grp *g, char *name) {
    s32 i;
    Ent *e;
    if (name == 0) {
        return 0;
    }
    e = g->x28;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < g->x2C; i++, e++) {
        if (*name == *e->name && StrNotEqual_1f5300(e->name + 1, name + 1) == 0) {
            return e;
        }
    }
    return 0;
}

static inline s32 Try1(Ent *e, unsigned long long mask, f32 f) {
    u8 *q;
    s32 i;
    q = e->x20;
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < e->x32; i++, q += 0x14) {
        if ((mask & ActDataCnctGetCmndMask_2274c0(q + 0xC)) == ActDataCnctGetCmndMask_2274c0(q + 0xC)) {
            if (ActionEntryTimeMatch_228310(q, f)) {
                return ((s32)ActTimeCnctGetCnct_227540(q + 0xC));
            }
        }
    }
    return 0;
}

static inline u8 *Try2(Grp *g, unsigned long long mask) {
    s32 i;
    u8 *q;
    q = g->x1C;
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < g->x24; i++, q += 8) {
        if ((mask & ActDataCnctGetCmndMask_2274c0(q)) == ActDataCnctGetCmndMask_2274c0(q)) {
            return q;
        }
    }
    return 0;
}

s32 ActCfgTableFindNormalCnctByMask_220d10(u8 *self, s32 key, char *name, unsigned long long mask, f32 f) {
    Node *found;
    Grp *g;
    Ent *e;
    s32 r;
    u8 *q;

    found = Lookup(self + 0x7C, key);
    if (found == 0) {
        g = 0;
    } else {
        g = &found->grp;
    }
    if (g == 0) {
        return 0;
    }
    e = Find(g, name);
    if (e != 0) {
        r = Try1(e, (unsigned long long)(mask), f);
        if (r != 0) {
            return r;
        }
    }
    q = Try2(g, (unsigned long long)(mask));
    if (q != 0) {
        return (s32)q;
    }
    if (e != 0) {
        if ((r = ActCfgTableFindCnctByMaskRefs_2208a0(self, e->x4, e->x24, (long long)(mask), f)) != 0) {
            return r;
        }
    }
    return 0;
}
