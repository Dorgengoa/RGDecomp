/* rgp:protos */
#define RGP_SELF_PoolAllocAppendNode_2543f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    u8 unk00[0x5C];
    struct Node *unk5C;
} Node;

typedef struct Obj {
    u8 unk00[0x10];
    Node *unk10;
    Node *unk14;
} Obj;

/*rgp*/

Node *PoolAllocAppendNode_2543f0(Obj *o)
{
    Node *n;
    Node *t;

    n = ((Node *)EventCameraNodeFindFree_2544b0(o));
    if (n == NULL) {
        return NULL;
    }
    t = o->unk14;
    if (t != NULL) {
        t->unk5C = n;
    }
    o->unk14 = n;
    n->unk5C = NULL;
    if (o->unk10 == NULL) {
        o->unk10 = n;
    }
    return n;
}
