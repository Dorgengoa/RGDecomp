#include "types.h"

typedef struct Node {
    struct Node *unk0;
    struct Node *unk4;
    struct Node *unk8;
} Node;

void RbTreeIncrement_1a2210(Node **arg0) {
    Node *n;
    Node *p;

    n = (*arg0)->unk4;
    if (n != NULL) {
        while (n->unk0 != NULL) {
            n = n->unk0;
        }
        *arg0 = n;
    } else {
        for (;;) {
            p = *arg0;
            n = (Node *)((u32)p->unk8 & ~1);
            if (p == n->unk0) {
                *arg0 = n;
                break;
            }
            *arg0 = n;
        }
    }
}
