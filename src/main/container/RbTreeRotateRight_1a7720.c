#include "types.h"

struct N1a7720 { struct N1a7720 *left; struct N1a7720 *right; u32 parent; };

void RbTreeRotateRight_1a7720(struct N1a7720 *x, struct N1a7720 **root)
{
    struct N1a7720 *y;
    struct N1a7720 *p;

    y = x->left;
    if (*root == x) {
        *root = y;
    }
    x->left = y->right;
    if (y->right != 0) {
        y->right->parent = (u32)x | (y->right->parent & 1);
    }
    y->parent = (x->parent & ~1) | (y->parent & 1);
    p = (struct N1a7720 *)(x->parent & ~1);
    if (x == p->left) {
        p->left = y;
    } else {
        p->right = y;
    }
    y->right = x;
    x->parent = (u32)y | (x->parent & 1);
}
