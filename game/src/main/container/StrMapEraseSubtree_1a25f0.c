/* rgp:protos */
#define RGP_SELF_StrMapEraseSubtree_1a25f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_001a25f0 {
    s32 f00;
    s32 f04;
    void *f08;
} Str_001a25f0;

typedef struct Node_001a25f0 {
    struct Node_001a25f0 *l;   /* +0x00 */
    struct Node_001a25f0 *r;   /* +0x04 */
    s32 m08;                   /* +0x08 */
    Str_001a25f0 s;            /* +0x0C */
} Node_001a25f0;

extern void StrMapEraseSubtree_1a25f0(void *env, Node_001a25f0 *p);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StrMapEraseSubtree_1a25f0(void *env, Node_001a25f0 *p)
{
    Node_001a25f0 *n;
    Node_001a25f0 *m;
    Str_001a25f0 *q;

    n = p->l;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a25f0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a25f0(env, m->r);
            }
            StringDestroy_1a28f0(StrMapGetValueAlloc_1a2930(env), &m->s);
            StrMapNodeDealloc_1a28d0(StrMapGetNodeAlloc_1a28e0(env), m);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a25f0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a25f0(env, m->r);
            }
            StringDestroy_1a28f0(StrMapGetValueAlloc_1a2930(env), &m->s);
            StrMapNodeDealloc_1a28d0(StrMapGetNodeAlloc_1a28e0(env), m);
        }
        StrMapGetValueAlloc_1a2930(env);
        StringDtor_1a2860(&n->s, -1);
        StrMapGetNodeAlloc_1a28e0(env);
        OperatorDelete_100840(n);
    }
    n = p->r;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a25f0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a25f0(env, m->r);
            }
            StringDestroy_1a28f0(StrMapGetValueAlloc_1a2930(env), &m->s);
            StrMapNodeDealloc_1a28d0(StrMapGetNodeAlloc_1a28e0(env), m);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a25f0(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a25f0(env, m->r);
            }
            StringDestroy_1a28f0(StrMapGetValueAlloc_1a2930(env), &m->s);
            StrMapNodeDealloc_1a28d0(StrMapGetNodeAlloc_1a28e0(env), m);
        }
        StrMapGetValueAlloc_1a2930(env);
        StringDtor_1a2860(&n->s, -1);
        StrMapGetNodeAlloc_1a28e0(env);
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
