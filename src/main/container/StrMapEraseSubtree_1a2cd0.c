#include "types.h"

typedef struct Str_001a2cd0 {
    s32 f00;
    s32 f04;
    void *f08;
} Str_001a2cd0;

typedef struct Node_001a2cd0 {
    struct Node_001a2cd0 *l;   /* +0x00 */
    struct Node_001a2cd0 *r;   /* +0x04 */
    s32 m08;                   /* +0x08 */
    Str_001a2cd0 s;            /* +0x0C */
} Node_001a2cd0;

extern void StrMapEraseSubtree_1a2cd0(void *env, Node_001a2cd0 *p);
extern void *StrMapGetValueAlloc_1a3010(void *env);
extern void StringDestroy_1a2fd0(void *h, Str_001a2cd0 *s);
extern void *StrMapGetNodeAlloc_1a2fc0(void *env);
extern void StrMapNodeDealloc_1a2fb0(void *h, Node_001a2cd0 *m, s32 f);
extern void StringDtor_1a2f40(Str_001a2cd0 *s, s32 v);
extern void OperatorDelete_100840(void *p);

void StrMapEraseSubtree_1a2cd0(void *env, Node_001a2cd0 *p)
{
    Node_001a2cd0 *n;
    Node_001a2cd0 *m;
    Str_001a2cd0 *q;

    n = p->l;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->r);
            }
            StringDestroy_1a2fd0(StrMapGetValueAlloc_1a3010(env), &m->s);
            StrMapNodeDealloc_1a2fb0(StrMapGetNodeAlloc_1a2fc0(env), m, 1);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->r);
            }
            StringDestroy_1a2fd0(StrMapGetValueAlloc_1a3010(env), &m->s);
            StrMapNodeDealloc_1a2fb0(StrMapGetNodeAlloc_1a2fc0(env), m, 1);
        }
        StrMapGetValueAlloc_1a3010(env);
        StringDtor_1a2f40(&n->s, -1);
        StrMapGetNodeAlloc_1a2fc0(env);
        OperatorDelete_100840(n);
    }
    n = p->r;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->r);
            }
            StringDestroy_1a2fd0(StrMapGetValueAlloc_1a3010(env), &m->s);
            StrMapNodeDealloc_1a2fb0(StrMapGetNodeAlloc_1a2fc0(env), m, 1);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2cd0(env, m->r);
            }
            StringDestroy_1a2fd0(StrMapGetValueAlloc_1a3010(env), &m->s);
            StrMapNodeDealloc_1a2fb0(StrMapGetNodeAlloc_1a2fc0(env), m, 1);
        }
        StrMapGetValueAlloc_1a3010(env);
        StringDtor_1a2f40(&n->s, -1);
        StrMapGetNodeAlloc_1a2fc0(env);
        OperatorDelete_100840(n);
    }
    q = &p->s;
    if (q != 0) {
        if (q != 0) {
            if ((p->s.f00 & 1) != 0) {
                OperatorDelete_100840(p->s.f08);
            }
        }
    }
    OperatorDelete_100840(p);
}
