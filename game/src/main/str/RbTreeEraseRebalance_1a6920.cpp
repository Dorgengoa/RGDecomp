#include "types.h"
#pragma opt_lifetimes off

struct Node {
    Node *left;
    Node *right;
    u32 pc;
    Node *parent() { return (Node *)(pc & ~1); }
    bool isRed() { return pc & 1; }
    bool isRedC() const { return pc & 1; }
    void setRed() { pc |= 1; }
    void setBlack() { pc &= ~1; }
    void setParent(Node *p) { pc = (u32)p | (pc & 1); }
};


extern "C" void RbTreeRotateLeft_1a76a0(Node *, Node **);
extern "C" void RbTreeRotateRight_1a7720(Node *, Node **);

extern "C" void RbTreeEraseRebalance_1a6920(Node *z, Node *volatile root)
{
    Node *y;
    Node *x;
    Node *xp;
    Node *w;
    Node *p;
    bool left;
    bool black;

    y = z;
    if (((const Node *)z)->left != 0 && ((const Node *)z)->right != 0) {
        if ((x = y->right) != 0) {
            while (x->left != 0) {
                x = x->left;
            }
            y = x;
        } else {
            while (y != y->parent()->left) {
                y = y->parent();
            }
            y = y->parent();
        }
    }
    x = y->left != 0 ? y->left : y->right;
    xp = y->parent();
    if (x != 0) {
        x->setParent(xp);
    }
    p = y->parent();
    if (y == p->left) {
        p->left = x;
        left = true;
    } else {
        p->right = x;
        left = false;
    }
    black = y->isRedC() == false;
    if (y != z) {
        y->setParent(z->parent());
        p = y->parent();
        if (z == p->left) {
            p->left = y;
        } else {
            p->right = y;
        }
        y->left = z->left;
        if (y->left != 0) {
            y->left->setParent(y);
        } else {
            xp = y;
        }
        y->right = z->right;
        if (y->right != 0) {
            y->right->setParent(y);
        } else {
            xp = y;
        }
        if (z->isRed() != false) {
            y->setRed();
        } else {
            y->setBlack();
        }
        if (root == z) {
            root = y;
        }
    } else if (x == 0 && z == root) {
        black = false;
    }
    if (black) {
        while (x != root && (x == 0 || x->isRed() == false)) {
            if (left) {
                w = xp->right;
                if (w->isRed() == true) {
                    w->setBlack();
                    xp->setRed();
                    RbTreeRotateLeft_1a76a0(xp, (Node **)&root);
                    w = xp->right;
                }
                if ((w->left == 0 || w->left->isRed() == false) && (w->right == 0 || w->right->isRed() == false)) {
                    w->setRed();
                    x = xp;
                    xp = xp->parent();
                    left = x == xp->left;
                } else {
                    if (w->right == 0 || w->right->isRed() == false) {
                        w->left->setBlack();
                        w->setRed();
                        RbTreeRotateRight_1a7720(w, (Node **)&root);
                        w = xp->right;
                    }
                    if (xp->isRed() != false) {
                        w->setRed();
                    } else {
                        w->setBlack();
                    }
                    xp->setBlack();
                    w->right->setBlack();
                    RbTreeRotateLeft_1a76a0(xp, (Node **)&root);
                    x = root;
                }
            } else {
                w = xp->left;
                if (w->isRed() == true) {
                    w->setBlack();
                    xp->setRed();
                    RbTreeRotateRight_1a7720(xp, (Node **)&root);
                    w = xp->left;
                }
                if ((w->left == 0 || w->left->isRed() == false) && (w->right == 0 || w->right->isRed() == false)) {
                    w->setRed();
                    x = xp;
                    xp = xp->parent();
                    left = x == xp->left;
                } else {
                    if (w->left == 0 || w->left->isRed() == false) {
                        w->right->setBlack();
                        w->setRed();
                        RbTreeRotateLeft_1a76a0(w, (Node **)&root);
                        w = xp->left;
                    }
                    if (xp->isRed() != false) {
                        w->setRed();
                    } else {
                        w->setBlack();
                    }
                    xp->setBlack();
                    w->left->setBlack();
                    RbTreeRotateRight_1a7720(xp, (Node **)&root);
                    x = root;
                }
            }
        }
        if (x != 0) {
            x->setBlack();
        }
    }
}
