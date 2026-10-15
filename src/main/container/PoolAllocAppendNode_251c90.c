#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x30];
    Node *unk30;
    Node *unk34;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251c90(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk34;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk34 = n;
    n->unk4C = NULL;
    if (o->unk30 == NULL) {
        o->unk30 = n;
    }
    return n;
}
