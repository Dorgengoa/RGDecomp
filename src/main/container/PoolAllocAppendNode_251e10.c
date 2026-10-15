#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x10];
    Node *unk10;
    Node *unk14;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251e10(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk14;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk14 = n;
    n->unk4C = NULL;
    if (o->unk10 == NULL) {
        o->unk10 = n;
    }
    return n;
}
