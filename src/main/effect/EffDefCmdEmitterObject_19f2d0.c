#include "types.h"

typedef union {
    s32 h;
    f32 f;
} Handle;

typedef struct Node {
    struct Node *next;
    s32 val;
} Node;

typedef struct {
    u8 pad0[0x70];
    Node *head;
    s32 count;
} List;

typedef struct {
    s32 base;
    u8 pad4[0x1C];
    s32 heap;
    List *list;
    u8 pad28[0xC];
    Node *node;
} Obj;

extern void *MemStackNew_14e230(s32, s32);
extern s8 *SlotGetInt_15f720(void);
extern void EffHdlRemove_1a3c80(s32, Handle);
extern void EffHdlAddByName_1a3d40(Handle *, s32, s8 *, Node **);

static inline s32 IsNull(Handle *h) {
    return !h->h;
}

static inline s32 *Append(List *l, s32 heap) {
    Node *n;
    Node *p;

    n = (Node *)MemStackNew_14e230(8, heap);
    if (n != NULL) {
        n->val = 0;
        n->next = NULL;
    }
    if (n == NULL) {
        return NULL;
    }
    l->count = 0;
    p = l->head;
    if (p != NULL) {
        for (; p != NULL; p = p->next) {
            if (p->next == NULL) {
                break;
            }
        }
        p->next = n;
    } else {
        l->head = n;
    }
    return &n->val;
}

s32 EffDefCmdEmitterObject_19f2d0(s32 pad0, s32 pad1, Obj **arg2)
{
    Handle sp5C;
    Node *sp58;
    Handle sp54;
    Obj *obj;
    s32 heap;
    s8 *name;
    Node *node;
    s32 *slot;

    obj = *arg2;
    heap = obj->heap;
    name = SlotGetInt_15f720();
    if (name == NULL || *name == 0) {
        return 0;
    }
    node = (Node *)MemStackNew_14e230(8, heap);
    if (node != NULL) {
        node->next = NULL;
        node->val = 0;
    }
    if (node == NULL) {
        return 0;
    }
    sp58 = node;
    EffHdlAddByName_1a3d40(&sp5C, obj->base + 0x7C, name, &sp58);
    if (IsNull(&sp5C)) {
        return 0;
    }
    slot = Append(obj->list, heap);
    if (slot == NULL) {
        sp54 = sp5C;
        EffHdlRemove_1a3c80(obj->base + 0x7C, sp54);
        return 0;
    }
    *slot = sp5C.h;
    obj->node = node;
    return 1;
}
