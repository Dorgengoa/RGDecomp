#include "types.h"

struct Node {
    struct Node *next;
    void *val;
};

struct Obj {
    u8 pad000[0x64];
    struct Node *head;
};

extern void *MemStackNew_14e230(s32 size);

void PtrListAppend_1a9800(struct Obj *a, s32 unused, void *c)
{
    struct Node *n;
    struct Node *p;

    if (c == 0) {
        return;
    }
    n = (struct Node *)MemStackNew_14e230(8);
    if (n != 0) {
        n->next = 0;
    }
    if (n == 0) {
        return;
    }
    n->val = c;
    p = a->head;
    if (p != 0) {
        while (p != 0) {
            if (p->next == 0) {
                break;
            }
            p = p->next;
        }
        p->next = n;
        return;
    }
    a->head = n;
}
