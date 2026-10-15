#include "types.h"

typedef struct Node {
    u8 unk00[0x5C];
    struct Node *unk5C;
} Node;

typedef struct Obj {
    u8 unk00[0x8];
    Node *unk8;
    Node *unkC;
} Obj;

extern Node *EventCameraNodeFindFree_2544b0(Obj *);

Node *PoolAllocAppendNode_254450(Obj *o)
{
    Node *n;
    Node *t;

    n = EventCameraNodeFindFree_2544b0(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unkC;
    if (t != NULL) {
        t->unk5C = n;
    }
    o->unkC = n;
    n->unk5C = NULL;
    if (o->unk8 == NULL) {
        o->unk8 = n;
    }
    return n;
}
