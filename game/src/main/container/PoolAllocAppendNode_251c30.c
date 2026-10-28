/* rgp:protos */
#define RGP_SELF_PoolAllocAppendNode_251c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    u8 unk00[0x4C];
    struct Node *unk4C;
} Node;

typedef struct Obj {
    u8 unk00[0x38];
    Node *unk38;
    Node *unk3C;
} Obj;

/*rgp*/

Node *PoolAllocAppendNode_251c30(Obj *o)
{
    Node *n;
    Node *t;

    n = ((Node *)EventSubNodeFindFree_251f10(o));
    if (n == NULL) {
        return NULL;
    }
    t = o->unk3C;
    if (t != NULL) {
        t->unk4C = n;
    }
    o->unk3C = n;
    n->unk4C = NULL;
    if (o->unk38 == NULL) {
        o->unk38 = n;
    }
    return n;
}
