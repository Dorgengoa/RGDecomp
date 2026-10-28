/* rgp:protos */
#define RGP_SELF_EffDefCmdEffectObject_19f0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 body[0x40];
} Node;

typedef struct Tbl {
    u8 pad[0x8C];
    Node *list;
    s32 x88;
} Tbl;

typedef struct Obj {
    u8 pad[0x20];
    s32 heap;
    Tbl *tbl;
    u8 *x28;
    u8 *x2C;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EffDefCmdEffectObject_19f0f0(s32 unused0, s32 unused1, Obj **arg2)
{
    Obj *o;
    s32 id;
    Tbl *t;
    Node *n;
    Node *p;
    u8 *rec;

    o = *arg2;
    id = SlotGetInt_15f720((void *)unused0);
    if (id == 0) {
        return 0;
    }
    t = o->tbl;
    n = ((Node *)MemStackNew_14e230(0x44, o->heap));
    if (n != NULL) {
        EffObjBaseCtor_1a9ed0(n->body);
        n->next = NULL;
    }
    if (n == NULL) {
        rec = NULL;
    } else {
        t->x88 = 0;
        p = t->list;
        if (p != NULL) {
            while (p != NULL) {
                if (p->next == NULL) {
                    break;
                }
                p = p->next;
            }
            p->next = n;
        } else {
            t->list = n;
        }
        rec = n->body;
    }
    o->x28 = rec;
    if (o->x28 == NULL) {
        return 0;
    }
    SetDupString_1a9ea0(o->x28, o->heap, id);
    return 1;
}
