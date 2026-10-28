/* rgp:protos */
#define RGP_SELF_PoolAllocAppendNode_254390 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/

Node *PoolAllocAppendNode_254390(Obj *o)
{
    Node *n;
    Node *t;

    n = ((Node *)EventCameraNodeFindFree_2544b0(o));
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
