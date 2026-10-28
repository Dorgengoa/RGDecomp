/* rgp:protos */
#define RGP_SELF_SceneTreeInsertNamed_19ade0 1
#define RGP_SELF_findName 1
#define RGP_SELF_newItem 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    s32 name;
} Node;

typedef struct Item {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 *xC;
    s32 x10;
} Item;

typedef struct Obj {
    u8 pad0[0x7C];
    Node *x7C;
    u8 pad80[0x14];
    Item *x94;
    Item *x98;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strcmp(s32, s32);

static inline s32 *findName(Obj *self, s32 name)
{
    Node *n;
    s32 *p;
    if (name == 0) {
        return NULL;
    }
    for (n = self->x7C; n != NULL; n = n->next) {
        p = &n->name;
        if (p != NULL && *p != 0 && strcmp(name, *p) == 0) {
            return p;
        }
    }
    return NULL;
}

static inline Item *newItem(s32 heap, s32 *ref, s32 name)
{
    Item *it;
    it = ((Item *)MemStackNew_14e230(0x18, heap));
    if (it != NULL) {
        it->xC = 0;
        it->x8 = 0;
        it->x4 = 0;
        it->x0 = 0;
    }
    if (it == NULL) {
        return NULL;
    }
    it->xC = ref;
    it->x10 = ((s32)MemStackStrDup_14cf10(name, heap));
    return it;
}

void SceneTreeInsertNamed_19ade0(Obj *self, s32 heap, s32 name, s32 name2, s32 key)
{
    s32 *ref;
    Item *it;
    Item *found;
    Item *head;
    s32 nm;

    nm = name2;
    if (nm == 0) {
        nm = name;
    }
    if (name == 0) {
        it = NULL;
    } else {
        ref = findName(self, name);
        if (ref == NULL) {
            it = NULL;
        } else {
            it = newItem(heap, ref, nm);
        }
    }
    if (it == NULL) {
        return;
    }
    if (key == 0) {
        found = NULL;
    } else {
        self->x98 = self->x94;
        while ((found = ((Item *)TreeIterNext_19ad60(self))) != NULL) {
            if (found->x10 != 0 && strcmp(found->x10, key) == 0) {
                break;
            }
        }
        self->x98 = NULL;
    }
    if (found != NULL) {
        SceneTreeAttachChild_19b320(found, it);
        return;
    }
    head = self->x94;
    if (head != NULL) {
        ListAppendTail_19b1f0(head, it);
    } else {
        self->x94 = it;
    }
}
