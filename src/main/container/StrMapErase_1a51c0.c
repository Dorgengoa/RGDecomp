#include "types.h"

extern void OperatorDelete_100840(void *);
extern void RbTreeEraseRebalance_1a6920(void *n, void *head);

struct Str51c0 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

struct Node51c0 {
    struct Node51c0 *left;      /* +0x00 */
    struct Node51c0 *right;     /* +0x04 */
    s32 parent;                 /* +0x08, colour in bit 0 */
    struct Str51c0 val;         /* +0x0C */
};

struct Tree51c0 {
    s32 size;                   /* +0x00 */
    void *head;                 /* +0x04 */
    u8 pad008[0x4];
    struct Node51c0 *lmost;     /* +0x0C */
};

void StrMapErase_1a51c0(struct Tree51c0 *t, struct Node51c0 **it)
{
    struct Node51c0 *n;
    struct Node51c0 *p;
    struct Node51c0 *q;
    struct Node51c0 *r;
    struct Node51c0 **h;
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
                p = (struct Node51c0 *)(q->parent & -2);
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
