/* rgp:protos */
#define RGP_SELF_RbTreeRotateLeft_1a76a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct N1a76a0 { struct N1a76a0 *left; struct N1a76a0 *right; u32 parent; };

void RbTreeRotateLeft_1a76a0(struct N1a76a0 *x, struct N1a76a0 **root)
{
    struct N1a76a0 *y;
    struct N1a76a0 *p;

    y = x->right;
    if (*root == x) {
        *root = y;
    }
    x->right = y->left;
    if (y->left != 0) {
        y->left->parent = (u32)x | (y->left->parent & 1);
    }
    y->parent = (x->parent & ~1) | (y->parent & 1);
    p = (struct N1a76a0 *)(x->parent & ~1);
    if (x == p->left) {
        p->left = y;
    } else {
        p->right = y;
    }
    y->left = x;
    x->parent = (u32)y | (x->parent & 1);
}
