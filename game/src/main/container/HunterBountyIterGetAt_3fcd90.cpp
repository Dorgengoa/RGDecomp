/* rgp:protos */
#line 1
#include "types.h"

struct Ent {
    u8 pad[32];
};

struct Tbl {
    u8 pad0[0x7c];
    s16 count;
    u8 pad7e[0xe];
    Ent *ents;
    Ent *Get(s32 i) {
        return (i >= 0 && Has(i)) ? &ents[i] : 0;
    }
    bool Has(s32 i) { return i < count; }
};

struct It {
    s32 m0;
    Tbl *tbl;
    s16 n;
    s16 cur;
    s16 slot;
};

extern "C" s32 HunterBountyIterMatch_3fd070(It *, Ent *);

extern "C" Ent *HunterBountyIterGetAt_3fcd90(It *it, s32 k)
{
    s32 n;
    s32 cnt;
    Tbl *t;
    s32 i;
    Ent *e;

    if ((t = it->tbl) == 0) {
        return 0;
    }
    if (k < 0 || k >= it->n) {
        return 0;
    }
    if (k == it->cur) {
        return t->Get(it->slot);
    }
    cnt = 0;
    i = 0;
    if (k == it->cur + 1) {
        cnt = it->cur + 1;
        i = it->slot + 1;
    }
    n = t->count;
    for (; i < n; i++) {
        e = it->tbl->Get(i);
        if ((u8)((unsigned char)HunterBountyIterMatch_3fd070(it, e))) {
            if (cnt == k) {
                it->cur = k;
                it->slot = i;
                return e;
            } else {
                cnt++;
            }
        }
    }
    it->cur = -1;
    it->slot = -1;
    return 0;
}
