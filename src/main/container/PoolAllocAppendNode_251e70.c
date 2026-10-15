#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x8];
    Node *unk8;
    Node *unkC;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251e70(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unkC;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unkC = n;
    n->unk4C = NULL;
    if (o->unk8 == NULL) {
        o->unk8 = n;
    }
    return n;
}
