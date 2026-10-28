/* rgp:protos */
#define RGP_SELF_ListAppendTail_19b1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma auto_inline on
#pragma inline_depth(7)
typedef struct Node { s32 x0; s32 x4; struct Node *next; } Node;

void ListAppendTail_19b1f0(Node *n, Node *a)
{
    if (n->next == NULL) {
        n->next = a;
    } else {
        ListAppendTail_19b1f0(n->next, a);
    }
    a->x0 = n->x0;
}
