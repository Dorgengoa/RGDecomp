#include "types.h"

struct Node {
    Node *left;
    Node *right;
    u32 pc;
    Node *parent() { return (Node *)(pc & ~1); }
    bool isRed() { return pc & 1; }
    void setRed() { pc |= 1; }
    void setBlack() { pc &= ~1; }
};

static inline Node *RP(Node *n) { return (Node *)(*(u32 *)((u8 *)n + 8) & ~1); }

extern "C" void RbTreeRotateLeft_1a76a0(Node *, Node **);
extern "C" void RbTreeRotateRight_1a7720(Node *, Node **);

extern "C" void RbTreeRebalance_1a7480(Node *x, Node *volatile root) {
    Node *y;
    Node *p;

    x->setRed();
    while (x != root && (p = x->parent())->isRed() == true) {
        if (RP(x) == RP(RP(x))->left) {
            y = RP(RP(x))->right;
            if (y != 0 && y->isRed() == true) {
                p->setBlack();
                y->setBlack();
                x = x->parent()->parent();
                x->setRed();
            } else {
                if (x == p->right) {
                    x = p;
                    RbTreeRotateLeft_1a76a0(x, (Node **)&root);
                }
                x->parent()->setBlack();
                x->parent()->parent()->setRed();
                RbTreeRotateRight_1a7720(x->parent()->parent(), (Node **)&root);
            }
        } else {
            y = RP(RP(x))->left;
            if (y != 0 && y->isRed() == true) {
                p->setBlack();
                y->setBlack();
                x = x->parent()->parent();
                x->setRed();
            } else {
                if (x == p->left) {
                    x = p;
                    RbTreeRotateRight_1a7720(x, (Node **)&root);
                }
                x->parent()->setBlack();
                x->parent()->parent()->setRed();
                RbTreeRotateLeft_1a76a0(x->parent()->parent(), (Node **)&root);
            }
        }
    }
    root->setBlack();
}
