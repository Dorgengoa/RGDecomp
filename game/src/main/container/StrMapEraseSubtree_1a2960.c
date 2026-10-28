/* rgp:protos */
#define RGP_SELF_StrMapEraseSubtree_1a2960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_001a2960 {
    s32 f00;
    s32 f04;
    void *f08;
} Str_001a2960;

typedef struct Node_001a2960 {
    struct Node_001a2960 *l;   /* +0x00 */
    struct Node_001a2960 *r;   /* +0x04 */
    s32 m08;                   /* +0x08 */
    Str_001a2960 s;            /* +0x0C */
} Node_001a2960;

extern void StrMapEraseSubtree_1a2960(void *env, Node_001a2960 *p);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StrMapEraseSubtree_1a2960(void *env, Node_001a2960 *p)
{
    Node_001a2960 *n;
    Node_001a2960 *m;
    Str_001a2960 *q;

    n = p->l;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2960(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2960(env, m->r);
            }
            StringDestroy_1a2c60(StrMapGetValueAlloc_1a2ca0(env), &m->s);
            StrMapNodeDealloc_1a2c40(StrMapGetNodeAlloc_1a2c50(env), m);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2960(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2960(env, m->r);
            }
            StringDestroy_1a2c60(StrMapGetValueAlloc_1a2ca0(env), &m->s);
            StrMapNodeDealloc_1a2c40(StrMapGetNodeAlloc_1a2c50(env), m);
        }
        StrMapGetValueAlloc_1a2ca0(env);
        StringDtor_1a2bd0(&n->s, -1);
        StrMapGetNodeAlloc_1a2c50(env);
        OperatorDelete_100840(n);
    }
    n = p->r;
    if (n != 0) {
        m = n->l;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2960(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2960(env, m->r);
            }
            StringDestroy_1a2c60(StrMapGetValueAlloc_1a2ca0(env), &m->s);
            StrMapNodeDealloc_1a2c40(StrMapGetNodeAlloc_1a2c50(env), m);
        }
        m = n->r;
        if (m != 0) {
            if (m->l != 0) {
                StrMapEraseSubtree_1a2960(env, m->l);
            }
            if (m->r != 0) {
                StrMapEraseSubtree_1a2960(env, m->r);
            }
            StringDestroy_1a2c60(StrMapGetValueAlloc_1a2ca0(env), &m->s);
            StrMapNodeDealloc_1a2c40(StrMapGetNodeAlloc_1a2c50(env), m);
        }
        StrMapGetValueAlloc_1a2ca0(env);
        StringDtor_1a2bd0(&n->s, -1);
        StrMapGetNodeAlloc_1a2c50(env);
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
