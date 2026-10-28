/* rgp:protos */
#define RGP_SELF_PoolAllocAppendNode_2542d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    u8 unk00[0x5C];
    struct Node *unk5C;
} Node;

typedef struct Obj {
    u8 unk00[0x28];
    Node *unk28;
    Node *unk2C;
} Obj;

/*rgp*/

Node *PoolAllocAppendNode_2542d0(Obj *o)
{
    Node *n;
    Node *t;

    n = ((Node *)EventCameraNodeFindFree_2544b0(o));
    if (n == NULL) {
        return NULL;
    }
    t = o->unk2C;
    if (t != NULL) {
        t->unk5C = n;
    }
    o->unk2C = n;
    n->unk5C = NULL;
    if (o->unk28 == NULL) {
        o->unk28 = n;
    }
    return n;
}
