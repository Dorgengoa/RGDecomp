#pragma opt_common_subs off
#pragma always_inline on
#include "types.h"

struct Ent { s8 name[0x30]; };
struct Tbl { s32 x0; s32 count; Ent *data; };
struct Node { Node *next; s32 x4; s32 x8; s32 key; Tbl tbl; };
struct Grp { u8 pad0[0x48]; Node *list; };
struct GNode { GNode *next; s32 x4; s32 x8; s32 key; Grp grp; };
struct Mgr { s32 x0; GNode *head; GNode *iter; };

static inline bool StrEq(const s8 *a, const s8 *b)
{
    s8 c;
    if (*a != *b) return 0;
    while ((c = *a) != 0 || *b != 0) {
        if (c != *b) return 0;
        a++;
        b++;
    }
    return 1;
}

static inline s32 Find(Tbl *t, const s8 *name)
{
    s32 i;
    if (name == 0) return -1;
    if (t->data == 0) return 0;
    for (i = 0; i < t->count; i++) {
        if (StrEq(t->data[i].name, name)) return i;
    }
    return -1;
}

static inline s32 FindIdx(Grp *g, const s8 *name, s32 *outKey)
{
    Tbl *t;
    Node *p;
    s32 idx;
    for (p = g->list; p != 0; p = p->next) {
        t = &p->tbl;
        if (t != 0) {
            idx = Find(t, name);
            if (idx >= 0) {
                *outKey = p->key;
                return idx;
            }
        }
    }
    return -1;
}

static inline Node *FindNode(Grp *g, s32 key)
{
    Node *q;
    for (q = g->list; q != 0; q = q->next) {
        if (key == q->key) return q;
    }
    return 0;
}

static inline Ent *Get(Tbl *t, s32 i)
{
    Ent *d = t->data;
    int ok;
    if (d == 0) ok = 0;
    else if (i < 0 || i >= t->count) ok = 0;
    else ok = 1;
    if (ok) return &d[i];
    return 0;
}

static inline Grp *Next(Mgr *m, s32 *outKey)
{
    GNode *n = m->iter;
    Grp *g;
    if (n == 0) {
        g = 0;
    } else {
        g = &n->grp;
        *outKey = n->key;
        m->iter = m->iter->next;
    }
    return g;
}

extern "C" Ent *MotionListFindByName_1721d0(Mgr *self, const s8 *name, s32 *outGrp, s32 *outSub)
{
    Ent *r;
    Grp *g;
    Node *q;
    Tbl *s;
    s32 idx;
    Node *p;
    Tbl *t;
    r = 0;
    self->iter = self->head;
    while ((g = Next(self, outGrp)) != 0) {
        for (p = g->list; p != 0; p = p->next) {
            t = &p->tbl;
            if (t != 0) {
                idx = Find(t, name);
                if (idx >= 0) {
                    *outSub = p->key;
                    goto found;
                }
            }
        }
        idx = -1;
    found:
        if (idx < 0) continue;
        q = FindNode(g, *outSub);
        s = q ? &q->tbl : 0;
        if (s != 0) {
            r = Get(s, idx);
        }
        if (r != 0) break;
    }
    self->iter = 0;
    return r;
}
