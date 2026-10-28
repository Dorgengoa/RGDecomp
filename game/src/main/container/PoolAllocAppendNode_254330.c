/* rgp:protos */
#define RGP_SELF_PoolAllocAppendNode_254330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    u8 unk00[0x5C];
    struct Node *unk5C;
} Node;

typedef struct Obj {
    u8 unk00[0x20];
    Node *unk20;
    Node *unk24;
} Obj;

/*rgp*/

Node *PoolAllocAppendNode_254330(Obj *o)
{
    Node *n;
    Node *t;

    n = ((Node *)EventCameraNodeFindFree_2544b0(o));
    if (n == NULL) {
        return NULL;
    }
    t = o->unk24;
    if (t != NULL) {
        t->unk5C = n;
    }
    o->unk24 = n;
    n->unk5C = NULL;
    if (o->unk20 == NULL) {
        o->unk20 = n;
    }
    return n;
}
