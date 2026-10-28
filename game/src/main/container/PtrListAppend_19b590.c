/* rgp:protos */
#define RGP_SELF_PtrListAppend_19b590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Node {
    struct Node *next;
    void *val;
};

struct Obj {
    u8 pad000[0x44];
    struct Node *head;
};

/*rgp*/

void PtrListAppend_19b590(struct Obj *a, s32 unused, void *c)
{
    struct Node *n;
    struct Node *p;

    if (c == 0) {
        return;
    }
    n = (struct Node *)MemStackNew_14e230(8, (void *)unused);
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
