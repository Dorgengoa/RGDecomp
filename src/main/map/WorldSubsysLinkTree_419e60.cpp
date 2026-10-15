#include "types.h"

class VObj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void *Get(s16 id);
};

struct Tbl {
    u8 pad0[8];
    VObj *t8;
    VObj *tC;
    VObj *t10;
};

struct Ctx {
    u8 pad0[0x44];
    Tbl *t44;
    Tbl *t48;
    u8 pad4C[0x64 - 0x4C];
    Tbl *t64;
};

struct Node;

union Ref {
    s16 id;
    void *p;
};

union NRef {
    s16 id;
    Node *p;
};

struct Node {
    s16 key;
    u8 pad2[0xE];
    NRef parent;
    u8 pad14[4];
    s16 nchild;
    u8 pad1A[2];
    Node **child;
    Ref r20;
    u8 pad24[0x74 - 0x24];
    Ref r74;
    s16 n78;
    u8 pad7A[2];
    Ref *arr7C;
    u8 pad80[0x90 - 0x80];
    Ref r90;
};

extern "C" {
extern Node *IterNext_370040(void *);
extern void IterReset_3700f0(void *);
extern void IterInit_370170(void *, u8 *);
extern void ArenaCommit_370490(u8 *);
extern void ArenaSync_370540(u8 *, s32);
extern void *ArenaNew_41b5c0(s32, u8 *, s32, s32);

static inline Node *NextIt(void *p)
{
    return IterNext_370040(p);
}

s32 WorldSubsysLinkTree_419e60(u8 *arg0, Ctx *ctx)
{
    Node *n;
    Node *m;
    Node *p;
    s32 cnt;
    s32 j;
    s32 id;
    u8 *q;
    Node **out;
    s32 k;
    u8 it[8];
    u8 it2[8];

    if (ctx == NULL) {
        return 0;
    }
    q = arg0;
    if (q != NULL) {
        q += 0x88;
    }
    IterInit_370170(it, q);
    while ((n = IterNext_370040(it)) != NULL) {
        n->r20.p = ctx->t64->t8->Get(n->r20.id);
        id = n->parent.id;
        if (id >= 0) {
            n->parent.p = p = (Node *)ctx->t64->tC->Get(id);
            if (p != NULL) {
                p->nchild++;
            }
        } else {
            n->parent.p = 0;
        }
    }
    ArenaSync_370540(arg0 + 0x6C, 0);
    IterReset_3700f0(it);
    while ((n = IterNext_370040(it)) != NULL) {
        cnt = n->nchild;
        if (cnt > 0) {
            n->child = (Node **)ArenaNew_41b5c0(cnt * 4, arg0 + 0x6C, 4, -1);
            if (n->child != NULL) {
                out = n->child;
                k = 0;
                q = arg0;
                if (q != NULL) {
                    q += 0x88;
                }
                IterInit_370170(it2, q);
                while ((m = IterNext_370040(it2)) != NULL) {
                    if (m->parent.p != NULL && n->key == m->parent.p->key) {
                        *out++ = m;
                        if (++k >= cnt) {
                            break;
                        }
                    }
                }
            } else {
                n->nchild = 0;
            }
        }
    }
    ArenaCommit_370490(arg0 + 0x6C);
    IterReset_3700f0(it);
    while ((n = NextIt(it)) != NULL) {
        n->r74.p = ctx->t48->t8->Get(n->r74.id);
        if (n->arr7C != NULL) {
            for (j = 0; j < n->n78; j++) {
                n->arr7C[j].p = ctx->t44->t8->Get(n->arr7C[j].id);
            }
        }
        n->r90.p = ctx->t64->t10->Get(n->r90.id);
    }
    return 1;
}
}
