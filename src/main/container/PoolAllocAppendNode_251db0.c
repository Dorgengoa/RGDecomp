#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x18];
    Node *unk18;
    Node *unk1C;
} Obj;

extern Node *EventSubNodeFindFree_251f10(Obj *);

Node *PoolAllocAppendNode_251db0(Obj *o)
{
    Node *n;
    Node *t;

    n = EventSubNodeFindFree_251f10(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk1C;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk1C = n;
    n->unk4C = NULL;
    if (o->unk18 == NULL) {
        o->unk18 = n;
    }
    return n;
}
