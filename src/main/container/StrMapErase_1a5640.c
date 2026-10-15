#include "types.h"

extern void OperatorDelete_100840(void *);
extern void RbTreeEraseRebalance_1a6920(void *n, void *head);

struct Str5640 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

struct Node5640 {
    struct Node5640 *left;      /* +0x00 */
    struct Node5640 *right;     /* +0x04 */
    s32 parent;                 /* +0x08, colour in bit 0 */
    struct Str5640 val;         /* +0x0C */
};

struct Tree5640 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Node5640 *lmost;     /* +0x0C */
};

void StrMapErase_1a5640(struct Tree5640 *t, struct Node5640 **it)
{
    struct Node5640 *n;
    struct Node5640 *p;
    struct Node5640 *q;
    struct Node5640 *r;
    struct Node5640 **h;
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
                p = (struct Node5640 *)(q->parent & -2);
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
