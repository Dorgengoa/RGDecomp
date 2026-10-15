#include "types.h"

#pragma auto_inline on
#pragma inline_depth(5)

typedef struct Node Node;

struct Node {
    u8    pad00[0x48];
    Node *next;
};

void MemStackAppendSibling_14d6a0(Node *cur, Node *n)
{
    Node *p;

    if (n == NULL) {
        return;
    }
    p = cur->next;
    if (p != NULL) {
        MemStackAppendSibling_14d6a0(p, n);
    } else {
        cur->next = n;
        *(Node **)((u8 *)n + 0x44) = cur;
    }
}
