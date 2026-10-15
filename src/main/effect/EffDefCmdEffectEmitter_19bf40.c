#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 body[0x6C];
} Node;

typedef struct Tbl {
    u8 pad[0x84];
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

extern Node *MemStackNew_14e230(s32, s32);
extern s32 SlotGetInt_15f720();
extern void EffObjCtor_1a9af0(u8 *);
extern void SetDupString_1a9ea0(u8 *, s32, s32);

s32 EffDefCmdEffectEmitter_19bf40(s32 unused0, s32 unused1, Obj **arg2)
{
    Obj *o;
    s32 id;
    Tbl *t;
    Node *n;
    Node *p;
    u8 *rec;

    o = *arg2;
    id = SlotGetInt_15f720();
    if (id == 0) {
        return 0;
    }
    t = o->tbl;
    n = MemStackNew_14e230(0x70, o->heap);
    if (n != NULL) {
        EffObjCtor_1a9af0(n->body);
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
    o->x2C = rec;
    o->x28 = rec;
    if (o->x2C == NULL) {
        return 0;
    }
    SetDupString_1a9ea0(o->x2C, o->heap, id);
    return 1;
}
