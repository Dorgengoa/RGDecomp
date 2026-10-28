/* rgp:protos */
#define RGP_SELF_NodeObjUpdateMotions_194070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `beql $17,$0` with `sw $0,0x34($16)` in the delay slot is the branch-likely
   copy of the join block's first store: `e->m34 = 0;` sits AFTER the inner
   `if`.  Callee-saved locals descend from the highest, so the declaration
   order that gives $18/$17/$16 is node, thing, ent. */

typedef struct Thing Thing;
typedef struct Ent Ent;
typedef struct Node Node;

struct Ent {
    u8 pad000[0x34];
    void *m34;
    s32 m38;
    u8 pad03C[0x30];
    Thing *m6C;
};

struct Node {
    Node *m00;
    u8 pad004[0xC];
    Ent *m10;
};

typedef struct Owner {
    u8 pad000[0x94];
    Node *m94;
    u8 pad098[0x4];
    s32 m9C;
} Owner;

/*rgp*/
/*rgp*/

void NodeObjUpdateMotions_194070(Owner *p0)
{
    Node *n;
    Thing *t;
    Ent *e;

    if (p0->m9C == 0) {
        return;
    }
    n = p0->m94;
    while (n != 0) {
        e = n->m10;
        e->m34 = p0;
        e->m38 = 0;
        t = e->m6C;
        if (t != 0) {
            MotionListUpdateAll_171e40((u8 *)t + 0x1F0, 1.0f);
            ModelObjApplyMotionList_186700(t);
        }
        e->m34 = 0;
        e->m38 = 0;
        n = n->m00;
    }
}
