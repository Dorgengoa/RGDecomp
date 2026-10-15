#include "types.h"

typedef struct Node {
    u8 unk00[0x5C];
    struct Node *unk5C;
} Node;

typedef struct Obj {
    u8 unk00[0x18];
    Node *unk18;
    Node *unk1C;
} Obj;

extern Node *EventCameraNodeFindFree_2544b0(Obj *);

Node *PoolAllocAppendNode_254390(Obj *o)
{
    Node *n;
    Node *t;

    n = EventCameraNodeFindFree_2544b0(o);
    if (n == NULL) {
        return NULL;
    }
    t = o->unk1C;
    if (t != NULL) {
        t->unk5C = n;
    }
    o->unk1C = n;
    n->unk5C = NULL;
    if (o->unk18 == NULL) {
        o->unk18 = n;
    }
    return n;
}
