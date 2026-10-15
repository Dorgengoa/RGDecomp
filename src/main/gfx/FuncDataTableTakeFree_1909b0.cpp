#include "types.h"

struct ObjBase {
    u8 pad0[0x40];
    s32 m40;        /* 0x40 */
    u8 pad44[8];
};

class Obj : public ObjBase {
public:
    virtual void v0();
    virtual s32 v1(s32);
    virtual void v2();
};

typedef struct Node {
    struct Node *next;  /* 0x00 */
    struct Node *prev;  /* 0x04 */
    u8 pad8[8];
    Obj *obj;           /* 0x10 */
} Node;


typedef struct Mgr {
    u8 pad0[4];
    Node **tbl;         /* 0x04 */
} Mgr;

static inline Node *pop(Mgr *m)
{
    Node *n;
    Node *p;
    Node *nx;
    Node *t;

    n = *m->tbl;
    if (n == 0) {
        return 0;
    }
    p = n->prev;
    if (p != 0) {
        nx = n->next;
        p->next = nx;
        if (nx != 0) {
            nx->prev = p;
        }
        t = n->prev;
        while (t->prev != 0) {
            t = t->prev;
        }
    } else {
        nx = n->next;
        if (nx != 0) {
            nx->prev = 0;
        }
        t = n->next;
    }
    n->prev = 0;
    n->next = 0;
    *m->tbl = t;
    return n;
}

static inline Obj *link(Node **tbl, Node *n, s32 idx)
{
    Node *p;
    Obj *o;

    if (tbl == 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (idx < 0 || idx >= 13) {
        return 0;
    }
    if (tbl[idx] == 0) {
        tbl[idx] = n;
    } else {
        p = tbl[idx];
        while (p) {
            if (!p->next) {
                break;
            }
            p = p->next;
        }
        p->next = n;
        if (n) {
            n->prev = p;
        }
    }
    o = n->obj;
    o->m40 = idx;
    return o;
}

extern "C" Obj *FuncDataTableTakeFree_1909b0(Mgr *m, s32 idx)
{
    Node *n;
    Obj *o;

    if (idx >= 11) {
        return 0;
    }
    if (m->tbl == 0) {
        n = 0;
    } else {
        n = pop(m);
    }
    if (n == 0) {
        return 0;
    }
    n->obj->v2();
    o = link(m->tbl, n, idx);
    if (o->v1(0x271B) != 0) {
        return o;
    }
    o = 0;
    return o;
}
