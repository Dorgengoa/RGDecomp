/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/EventVoicePickChan_24f270.s and build/b_drafts/EventVoicePickChan_24f270.txt
   (m2c draft already generated, just not worked). Largest remaining draft
   in this lane (141 lines) -- likely wants a full session of its own. */
/* s49m: wrong length, ED 52 */
#include "types.h"

typedef struct Data {
    s32 k;
    s32 v;
    s32 p;
    s32 mC;
    u8 pad10[0x10];
    u8 m20;
    u8 pad21[3];
} Data;

typedef struct LNode {
    struct LNode *next;
    u8 pad4[8];
    s32 key;
    Data d;
} LNode;

typedef struct List {
    LNode *head;
    LNode *cur;
    s32 done;
    u8 padC[0x18];
    s32 arr[8];
    s32 n;
} List;

extern "C" {
extern s32 EventVoiceFindFreeChan_24fbf0(List *);
extern void *GetCurrentScene_1f5be0(void);
extern void *ObjRecGetLiveObject_1c4a90(void *, s32);
extern void ModelObjTexAnimResetByName_1ac510(void *, void *);
extern void *memset(void *, s32, u32);
}

static inline s32 begin(List *l)
{
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline Data *next(List *l, s32 *key)
{
    LNode *n;
    Data *d;

    n = l->cur;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    d = &n->d;
    l->cur = n->next;
    if (l->cur == 0) {
        l->done = 1;
    }
    return d;
}

static inline void end(List *l)
{
    l->cur = 0;
    l->done = 0;
}

extern "C" s32 EventVoicePickChan_24f270(List *l, s32 flag)
{
    Data *d;
    s32 key;
    s32 r;
    s32 k2;
    s32 best;
    s32 bestp;
    s32 bestk;
    s32 bestv;
    bool ok;
    s32 i;

    r = EventVoiceFindFreeChan_24fbf0(l);
    if (r >= 0) {
        return r;
    }
    best = -1;
    bestp = 0;
    bestk = 3;
    bestv = 0;
    if (begin(l) != 0) {
        return -1;
    }
    while ((d = next(l, &key)) != 0) {
        if (d->m20 == 1) {
            continue;
        }
        ok = false;
        if (flag != 0) {
            if (d->k < bestk || (d->k == bestk && bestp < d->p)) {
                ok = true;
            }
        } else if (bestp < d->p) {
            ok = true;
        }
        if (ok) {
            bestp = d->p;
            best = key;
            bestk = d->k;
            bestv = d->v;
        }
    }
    end(l);
    if (bestk == 1 && bestv > 0 && l->n < 8) {
        for (i = l->n; i > 0; i--) {
            l->arr[i] = l->arr[i - 1];
        }
        l->arr[0] = bestv;
        l->n++;
    }
    if (best <= -1) {
        return -1;
    }
    if (begin(l) != 0) {
        d = 0;
    } else {
        while ((d = next(l, &k2)) != 0) {
            if (best == k2) {
                break;
            }
        }
        end(l);
    }
    if (d == 0) {
        return -1;
    }
    if ((r = (s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), d->mC)) != 0) {
        ModelObjTexAnimResetByName_1ac510((void *)r, d->pad10);
    }
    memset(d, 0, 0x24);
    return best;
}
