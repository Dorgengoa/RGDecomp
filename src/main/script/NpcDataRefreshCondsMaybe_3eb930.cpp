#include "types.h"

struct Item {
    s16 *key;
    u8 pad4[0xC];
    s16 idx;
    u8 pad12[2];
    s16 h14;
    u8 pad16[2];
    s32 w18;
    s16 h1C[5];
    u8 pad26[0x48 - 0x26];
    s32 w48;
    u8 pad4C[0x56 - 0x4C];
    bool flag : 1;
};

struct Tab {
    u8 pad0[0xC];
    u8 *recs;
};

struct Mgr {
    u8 pad0[0x6C];
    Tab *tab;
};

struct Obj {
    u8 pad0[8];
    Mgr *mgr;
    u8 padC[4];
    s32 w10;
};

struct Big {
    u8 pad0[8];
    u8 elems[64][0x38];
    u8 tail[0x10];
};

extern "C" {
extern s32 VariantIsZero_36ed10(s32);
extern void VariantInit_36ff00(void *);
extern Item *IterNext_370040(void *);
extern void IterInit_370170(void *, u8 *);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern s32 ScriptExecOpStream_3dffa0(void *, s32, s32, s32);
extern void VariantPoolReset_3e01f0(void *);
extern Item *HandleEntryGet_3f24b0(Mgr *, s32);
extern const s32 D_004644A0[];
extern const s32 D_004644A8[];
extern s32 D_00466AB0[];

static inline u8 *GetRec(Mgr *m, s32 idx, s32 max)
{
    if (idx < 0 || idx >= max) {
        return 0;
    }
    return m->tab->recs + idx * 0x98;
}

static inline u8 *GetRec2(Mgr *m, s32 idx, s32 max)
{
    if (idx >= 0) {
        if (idx < max) {
            return m->tab->recs + idx * 0x98;
        }
    }
    return 0;
}

static inline bool InRange(s32 idx, s32 max)
{
    return idx >= 0 && idx < max;
}

static inline bool InRange2(s32 idx, s32 max)
{
    if (idx < 0) {
        return false;
    }
    return idx < max;
}

static inline u8 *GetRec3(Mgr *m, s32 idx, s32 max)
{
    return InRange(idx, max) ? m->tab->recs + idx * 0x98 : 0;
}

static inline u8 *GetRec4(Mgr *m, s32 idx, s32 max)
{
    return InRange2(idx, max) ? m->tab->recs + idx * 0x98 : 0;
}

static inline u8 *GetRec5(Mgr *m, s32 idx, s32 max)
{
    if (InRange(idx, max)) {
        return m->tab->recs + idx * 0x98;
    }
    return 0;
}

static inline u8 *GetT(Tab *t, s32 idx, s32 max)
{
    return InRange(idx, max) ? t->recs + idx * 0x98 : 0;
}

static inline Item *NextIt(void *p)
{
    return IterNext_370040(p);
}

s32 NpcDataRefreshCondsMaybe_3eb930(Obj *arg0, s32 arg1)
{
    s32 i;
    s32 max;
    s32 idx;
    Tab *tab;
    u8 *rec;
    Item *e;
    Item *it;
    u8 *p;
    s32 r;
    s32 j;
    Big big;
    u8 iter[8];
    if (arg0->mgr == NULL) {
        return 0;
    }
    max = D_004644A8[0];
    for (i = 0; i < D_004644A0[0]; i++) {
        e = HandleEntryGet_3f24b0(arg0->mgr, i);
        if (e == NULL) {
            continue;
        }
        if (e->key == NULL) {
            continue;
        }
        if (arg1 >= 0 && *e->key != arg1) {
            continue;
        }
        idx = e->idx;
        tab = arg0->mgr->tab;
        rec = InRange(idx, max) ? tab->recs + idx * 0x98 : 0;
        if (rec == 0) {
            continue;
        }
        if (rec != 0) {
            rec += 0x88;
        }
        IterInit_370170(iter, rec);
        while ((it = NextIt(iter)) != NULL) {
            it->flag = true;
            if (it->flag && it->h14 > 0 && it->w18 != 0) {
                p = big.elems[0];
                do {
                    VariantInit_36ff00(p);
                    p += 0x38;
                } while (p < big.tail);
                VariantPoolReset_3e01f0(&big);
                r = ScriptExecOpStream_3dffa0(&big, it->h14, it->w18, 0);
                if (r != 0 && VariantIsZero_36ed10(r) != 0) {
                    it->flag = false;
                }
            }
            if (it->flag) {
                it->w48 &= ~0x3E;
                for (j = 0; j < 5; j++) {
                    if (it->h1C[j] >= 0 && StateFlagTest_3ccd70(arg0->w10, it->h1C[j]) != 0) {
                        it->w48 = it->w48 | *(volatile s32 *)&D_00466AB0[j];
                    }
                }
            }
        }
    }
    return 1;
}
}
