#include "types.h"

typedef struct Str_001a2280 {
    s32 f00;
    s32 f04;
    void *f08;
} Str_001a2280;

typedef struct Node_001a2280 {
    struct Node_001a2280 *l;   /* +0x00 */
    struct Node_001a2280 *r;   /* +0x04 */
    s32 m08;                   /* +0x08 */
    Str_001a2280 s;            /* +0x0C */
} Node_001a2280;

extern void StrMapEraseSubtree_1a2280(void *env, Node_001a2280 *p);
extern void *StrMapGetValueAlloc_1a25c0(void *env);
extern void StringDestroy_1a2580(void *h, Str_001a2280 *s);
extern void *StrMapGetNodeAlloc_1a2570(void *env);
extern void StrMapNodeDealloc_1a2560(void *h, Node_001a2280 *m, s32 f);
extern void StringDtor_1a24f0(Str_001a2280 *s, s32 v);
extern void OperatorDelete_100840(void *p);

void StrMapEraseSubtree_1a2280(void *env, Node_001a2280 *p)
{
    Node_001a2280 *n;
    Node_001a2280 *m;
    Str_001a2280 *q;

    n = p->l;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2280(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2280(env, m->r);
            }
            StringDestroy_1a2580(StrMapGetValueAlloc_1a25c0(env), &m->s);
            StrMapNodeDealloc_1a2560(StrMapGetNodeAlloc_1a2570(env), m, 1);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2280(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2280(env, m->r);
            }
            StringDestroy_1a2580(StrMapGetValueAlloc_1a25c0(env), &m->s);
            StrMapNodeDealloc_1a2560(StrMapGetNodeAlloc_1a2570(env), m, 1);
        }
        StrMapGetValueAlloc_1a25c0(env);
        StringDtor_1a24f0(&n->s, -1);
        StrMapGetNodeAlloc_1a2570(env);
        OperatorDelete_100840(n);
    }
    n = p->r;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2280(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2280(env, m->r);
            }
            StringDestroy_1a2580(StrMapGetValueAlloc_1a25c0(env), &m->s);
            StrMapNodeDealloc_1a2560(StrMapGetNodeAlloc_1a2570(env), m, 1);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2280(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2280(env, m->r);
            }
            StringDestroy_1a2580(StrMapGetValueAlloc_1a25c0(env), &m->s);
            StrMapNodeDealloc_1a2560(StrMapGetNodeAlloc_1a2570(env), m, 1);
        }
        StrMapGetValueAlloc_1a25c0(env);
        StringDtor_1a24f0(&n->s, -1);
        StrMapGetNodeAlloc_1a2570(env);
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
