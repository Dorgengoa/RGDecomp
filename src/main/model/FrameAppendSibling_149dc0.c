#include "types.h"

#pragma auto_inline on
#pragma inline_depth(5)

typedef struct Node Node;

struct Node {
    u8    pad00[0xC];
    Node *next;
};

void FrameAppendSibling_149dc0(Node *cur, Node *n)
{
    Node *p;

    if (n == NULL) {
        return;
    }
    p = cur->next;
    if (p != NULL) {
        FrameAppendSibling_149dc0(p, n);
    } else {
        cur->next = n;
        *(Node **)((u8 *)n + 0x10) = cur;
    }
}
