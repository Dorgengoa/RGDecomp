#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x28];
    Node *unk28;
    Node *unk2C;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251cf0(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk2C;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk2C = n;
    n->unk4C = NULL;
    if (o->unk28 == NULL) {
        o->unk28 = n;
    }
    return n;
}
