#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x20];
    Node *unk20;
    Node *unk24;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251d50(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk24;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk24 = n;
    n->unk4C = NULL;
    if (o->unk20 == NULL) {
        o->unk20 = n;
    }
    return n;
}
