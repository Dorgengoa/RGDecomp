/* rgp:protos */
#define RGP_SELF_StrMapErase_1a5400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Str5400 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

struct Node5400 {
    struct Node5400 *left;      /* +0x00 */
    struct Node5400 *right;     /* +0x04 */
    s32 parent;                 /* +0x08, colour in bit 0 */
    struct Str5400 val;         /* +0x0C */
};

struct Tree5400 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Node5400 *lmost;     /* +0x0C */
};

void StrMapErase_1a5400(struct Tree5400 *t, struct Node5400 **it)
{
    struct Node5400 *n;
    struct Node5400 *p;
    struct Node5400 *q;
    struct Node5400 *r;
    struct Node5400 **h;
    s32 more;

    n = *it;
    if (n == t->lmost) {
        h = &t->lmost;
        p = n->right;
        if (p != 0) {
            while (p->left != 0) {
                p = p->left;
            }
            *it = p;
        } else {
            for (;;) {
                q = *it;
                p = (struct Node5400 *)(q->parent & -2);
                if (q == p->left) {
                    *it = p;
                    break;
                }
                *it = p;
            }
        }
        *h = *it;
    }
    RbTreeEraseRebalance_1a6920(n, t->head);
    if (&n->val != 0) {
        if (&n->val != 0) {
            if ((n->val.m00 & 1) != 0) {
                OperatorDelete_100840(n->val.m08);
            }
        }
    }
    OperatorDelete_100840(n);
    t->size = t->size - 1;
}
